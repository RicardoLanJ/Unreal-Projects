// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"


USTRUCT(BlueprintType)
struct FRecord {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FName Name;
	UPROPERTY(BlueprintReadWrite)
		int32 score;

	FRecord() {};

	FRecord(FName n, int32 s) {
		Name = n;
		score = s;
	};
};

/**
 * 
 */
UCLASS()
class GTA6_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<FRecord> rank;

	UFUNCTION(BlueprintCallable)
		bool AddRecord(const FName& name, int32 score);

	UMySaveGame();
};
