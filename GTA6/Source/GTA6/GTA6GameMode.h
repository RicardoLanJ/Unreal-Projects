// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "HUD/MainUIBPBase.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GTA6GameMode.generated.h"

UCLASS(minimalapi)
class AGTA6GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGTA6GameMode();

	//virtual void Tick(float DeltaSeconds) override;
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CountDownTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 DefaultTime = 10;

	FTimerHandle CountDownHandle;

	void StartTimer();

	void TimerCallBack();

	UFUNCTION(BlueprintNativeEvent)
	    void UpdateEachSecond();
	virtual void UpdateEachSecond_Implementation();

	void GameOver();
	
protected:
	
};



