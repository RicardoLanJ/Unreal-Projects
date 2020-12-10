// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverLineBase.generated.h"

/**
 * 
 */
UCLASS()
class GTA6_API UGameOverLineBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Kill;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Death;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ThePlayerName;
	
	void InitLineInfo(int32 Kill_, int32 Death_, FString& PlayerName);
};
