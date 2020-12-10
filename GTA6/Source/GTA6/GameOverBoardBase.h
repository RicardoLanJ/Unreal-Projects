// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverBoardBase.generated.h"

/**
 *
 */
UCLASS()
class GTA6_API UGameOverBoardBase : public UUserWidget
{
	GENERATED_BODY()

public:
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//	class UScrollBox* ScrollBox_52 = nullptr;
	
protected:
	virtual void NativeConstruct() override;;
	void AddLine(int32 KillNum, int32 DeathNum, FString PlayerName);
};
