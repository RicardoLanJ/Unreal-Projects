// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GTA6_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category = "Game|Player")
		void SetMousePosition(float LocationX, float LocationY);
};


