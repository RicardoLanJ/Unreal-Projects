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
			
			//实例化搜索结果指针并且设定参数
			SearchObject = MakeShareable(new FOnlineSessionSearch);
			//返回结果数
			SearchObject->MaxSearchResults = 10;
			//是否是局域网，就是IsLAN
			SearchObject->bIsLanQuery = true;
			SearchObject->QuerySettings.Set(SEARCH_PRESENCE, true,EOnlineComparisonOp::Equals);
			//绑定寻找会话委托
			OnFindSessionsCompleteDelegateHandle = Session->
				AddOnFindSessionsCompleteDelegate_Handle
				(OnFindSessionsCompleteDelegate);
			//进行会话寻找
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
			//解绑创建会话完成回调函数
			Session->
				ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			//判断创建会话是否成功
			if (bWasSuccessful)
			{

				//绑定开启会话委托
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
			//注销开启会话委托绑定
			Session->ClearOnStartSessionCompleteDelegate_Handle
			(OnStartSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				//服务端跳转场景
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
			//取消寻找会话委托绑定
			Session->ClearOnStartSessionCompleteDelegate_Handle
			(OnStartSessionCompleteDelegateHandle);
			//如果寻找会话成功
			if (bWasSuccessful)
			{
				//如果收集的结果存在且大于1
				if (SearchObject.IsValid() && SearchObject->SearchResults.Num() > 0)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Session nums! "));
					//绑定加入Session委托
					OnJoinSessionCompleteDelegateHandle = Session
						->AddOnJoinSessionCompleteDelegate_Handle
						(OnJoinSessionCompleteDelegate);
					//执行加入会话
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
			//取消加入对话委托绑定
			Session->ClearOnJoinSessionCompleteDelegate_Handle
			(OnJoinSessionCompleteDelegateHandle);
			//如果加入成功
			if (Result == EOnJoinSessionCompleteResult::Success)
			{
				FString ConnectString;
				if (Session->GetResolvedConnectString(NAME_GameSession, ConnectString))
				{
					//客户端切换到服务器的关卡
					GetWorld() -> GetFirstPlayerController() 
						->ClientTravel(ConnectString, TRAVEL_Absolute);
				}
			}
		}
	}
}
