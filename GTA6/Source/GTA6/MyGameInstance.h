// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Online.h"
#include "OnlineSubsystemUtils.h"

#include <GTA6\MySaveGame.h>
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class GTA6_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString PlayerName;
	UPROPERTY(BlueprintReadWrite)
		TArray<FRecord> Records;

	UFUNCTION(BlueprintCallable)
		bool HostSession();
	UFUNCTION(BlueprintCallable)
		bool FindSession();
	
	UMyGameInstance();

	void Init() override;
	
protected:
	IOnlineSubsystem* OnlineSub;
	TSharedPtr<FOnlineSessionSearch> SearchObject;
	
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	//����������ί��
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	//����������ί�о��
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	//���������ί��
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	//���������ί�о��
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
};

