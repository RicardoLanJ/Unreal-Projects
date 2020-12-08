// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Kismet/GameplayStatics.h"


bool UMyGameInstance::HostSession()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Host Session!"));
	
	//IOnlineSubsystem* const OnlineSub = Online::GetSubsystem(GetWorld(), NAME_None); // IOnlineSubsystem::Get();
	
	auto SessionSettings = MakeShareable(new FOnlineSessionSettings());
	
	//TSharedPtr<const FUniqueNetId> UserID = GEngine->GetWorld()->GetFirstLocalPlayerFromController()->GetPreferredUniqueNetId()->AsShared();
	if (GetLocalPlayers().Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("No local player!"));
		return false;
	}
	TSharedPtr<const FUniqueNetId> UserID = (*GetLocalPlayers()[0]->GetPreferredUniqueNetId()).AsShared();

	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid() && UserID.IsValid())
		{
			FOnlineSessionSettings Settings;

			Settings.NumPublicConnections = 4;
			Settings.NumPrivateConnections = 4;
			Settings.bShouldAdvertise = true;
			Settings.bAllowJoinInProgress = true;

			Settings.bIsLANMatch = true;
			Settings.bUsesPresence = true;
			Settings.bAllowJoinViaPresence = true;
			
			OnCreateSessionCompleteDelegateHandle = Session->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			if ( Session->CreateSession(*UserID, NAME_GameSession, Settings) )
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("create Session!"));
				return true;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("create Session fail!"));
			}
		} else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Invaild!"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("No onlineSubSystem found!"));
	}
	return false;
}

bool UMyGameInstance::FindSession()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			TSharedPtr<const FUniqueNetId> UserID = (*GetLocalPlayers()[0]->GetPreferredUniqueNetId()).AsShared();
			
			//ʵ�����������ָ�벢���趨����
			SearchObject = MakeShareable(new FOnlineSessionSearch);
			//���ؽ����
			SearchObject->MaxSearchResults = 10;
			//�Ƿ��Ǿ�����������IsLAN
			SearchObject->bIsLanQuery = true;
			SearchObject->QuerySettings.Set(SEARCH_PRESENCE, true,EOnlineComparisonOp::Equals);
			//��Ѱ�һỰί��
			OnFindSessionsCompleteDelegateHandle = Session->
				AddOnFindSessionsCompleteDelegate_Handle
				(OnFindSessionsCompleteDelegate);
			//���лỰѰ��
			Session->FindSessions(*UserID, SearchObject.ToSharedRef());
		}
	}
	return false;
}

UMyGameInstance::UMyGameInstance()
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::
		CreateUObject(this, &UMyGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::
		CreateUObject(this, &UMyGameInstance::OnStartSessionComplete);
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::
		CreateUObject(this, &UMyGameInstance::OnFindSessionComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::
		CreateUObject(this, &UMyGameInstance::OnJoinSessionComplete);
}

void UMyGameInstance::Init()
{
	UGameInstance::Init();
	OnlineSub = Online::GetSubsystem(GetWorld()); // IOnlineSubsystem::Get();
}

void UMyGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	//IOnlineSubsystem* const OnlineSub = Online::GetSubsystem(GetWorld(), NAME_None); // IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//��󴴽��Ự��ɻص�����
			Session->
				ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			//�жϴ����Ự�Ƿ�ɹ�
			if (bWasSuccessful)
			{

				//�󶨿����Ựί��
				OnStartSessionCompleteDelegateHandle = Session->
					AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Start Session! " + SessionName.ToString()));
				Session->StartSession(SessionName);
			}

		}
	}
}

void UMyGameInstance::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	//IOnlineSubsystem* const OnlineSub = Online::GetSubsystem(GetWorld(), NAME_None); // IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//ע�������Ựί�а�
			Session->ClearOnStartSessionCompleteDelegate_Handle
			(OnStartSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				//�������ת����
				UGameplayStatics::OpenLevel(GetWorld(),FName("ThirdPersonExampleMap"), true, FString("listen"));
			}
		}
	}
}

void UMyGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("find Session!"));
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			TSharedPtr<const FUniqueNetId> UserID = (*GetLocalPlayers()[0]->GetPreferredUniqueNetId()).AsShared();
			//ȡ��Ѱ�һỰί�а�
			Session->ClearOnStartSessionCompleteDelegate_Handle
			(OnStartSessionCompleteDelegateHandle);
			//���Ѱ�һỰ�ɹ�
			if (bWasSuccessful)
			{
				//����ռ��Ľ�������Ҵ���1
				if (SearchObject.IsValid() && SearchObject->SearchResults.Num() > 0)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Session nums! "));
					//�󶨼���Sessionί��
					OnJoinSessionCompleteDelegateHandle = Session
						->AddOnJoinSessionCompleteDelegate_Handle
						(OnJoinSessionCompleteDelegate);
					//ִ�м���Ự
					Session->JoinSession(*UserID, NAME_GameSession, SearchObject->SearchResults[0]);
				}
				//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Session zero! "));
			} else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("find Session fail! "));
			}

		}
	}
}

void UMyGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//ȡ������Ի�ί�а�
			Session->ClearOnJoinSessionCompleteDelegate_Handle
			(OnJoinSessionCompleteDelegateHandle);
			//�������ɹ�
			if (Result == EOnJoinSessionCompleteResult::Success)
			{
				FString ConnectString;
				if (Session->GetResolvedConnectString(NAME_GameSession, ConnectString))
				{
					//�ͻ����л����������Ĺؿ�
					GetWorld() -> GetFirstPlayerController() 
						->ClientTravel(ConnectString, TRAVEL_Absolute);
				}
			}
		}
	}
}
