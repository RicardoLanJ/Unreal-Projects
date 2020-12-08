// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkUtils.h"

#include "Online.h"
#include "OnlineSubsystemUtils.h"

NetworkUtils::NetworkUtils()
{
}

NetworkUtils::~NetworkUtils()
{
}

bool NetworkUtils::HostSession()
{
	//Online::GetSubsystem()
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	auto SessionSettings = MakeShareable(new FOnlineSessionSettings());

	TSharedPtr<const FUniqueNetId> UserID = GEngine->GetWorld()->GetFirstLocalPlayerFromController()-> GetPreferredUniqueNetId()->AsShared();
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid() && UserID.IsValid())
		{
			FOnlineSessionSettings Settings;

			Settings.NumPrivateConnections = 4;
			Settings.bShouldAdvertise = true;
			Settings.bAllowJoinInProgress = true;

			Settings.bIsLANMatch = true;
			//Settings.bUsesPresence = true;
			//Settings.bAllowJoinViaPresence = true;

			Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateStatic(&OnCreateSessionComplete));
			Session->CreateSession(*UserID,"MyGameSession", Settings);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("No onlineSubSystem found!"));
	}
	return false;
}

void NetworkUtils::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("create Session Complete!"));
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{

		}
	}
}
