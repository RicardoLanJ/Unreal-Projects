// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GTA6_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UPROPERTY(BlueprintReadOnly, Replicated)// ReplicatedUsing=OnRep_CountDownTime)
		int32 CountDownTime;
	//UFUNCTION()
	//	void OnRep_CountDownTime();
	
	//UFUNCTION(BlueprintImplementableEvent)
	//	void OnRep_CountDownTime();
};
