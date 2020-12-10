// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Net/UnrealNetwork.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 *
 */
UCLASS()
class GTA6_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMyPlayerState();
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		int32 KillNum;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		int32 DeathNum;
	UPROPERTY(BlueprintReadOnly, Replicated)
		FString ThePlayerName;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
		void AddOneDeathNum();
	UFUNCTION(BlueprintCallable)
		void AddKillNum(int32 kills = 1);
	UFUNCTION(server, Reliable)
		void InitPlayerInfo(const FString& PlayerName_);
		virtual void InitPlayerInfo_Implementation(const FString& PlayerName_);
protected:

};
