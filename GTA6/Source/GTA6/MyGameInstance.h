// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
		TArray<FRecord> records;
};
