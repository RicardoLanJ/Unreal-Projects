// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyStartMenuBase.generated.h"

/**
 * 
 */
UCLASS()
class GTA6_API UMyStartMenuBase : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintCallable)
		static void Host();
};
