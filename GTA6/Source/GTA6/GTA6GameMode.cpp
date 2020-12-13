// Copyright Epic Games, Inc. All Rights Reserved.

#include "GTA6GameMode.h"
#include "GTA6Character.h"
#include "MyGameStateBase.h"
#include "UObject/ConstructorHelpers.h"

#include "GameFramework/HUD.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"


AGTA6GameMode::AGTA6GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> StarBPClass(TEXT("/Game/ThirdPerson/star"));
	HUDClass = StarBPClass.Class;

	// PlayerControllerClass = AMyPlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<AMyPlayerController> PlayerContollerBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/MyMyPlayerController"));
	if (PlayerContollerBPClass.Class != NULL)
	{
	    PlayerControllerClass = PlayerContollerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AMyPlayerState> PlayerStateBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/MyPlayerStateBP"));
	if (PlayerStateBPClass.Class != NULL)
	{
		PlayerStateClass = PlayerStateBPClass.Class;
	}

}

void AGTA6GameMode::BeginPlay()
{
	StartTimer();
}


void AGTA6GameMode::StartTimer()
{
	CountDownTime = DefaultTime;
	//UpdateEachSecond();
	GetWorldTimerManager().SetTimer(CountDownHandle, this, &AGTA6GameMode::TimerCallBack, 1.0f, true);
}

void AGTA6GameMode::TimerCallBack()
{
	--CountDownTime;
	UpdateEachSecond();
	if (CountDownTime < 1)
        {
		GetWorldTimerManager().ClearTimer(CountDownHandle);
	}
}


void AGTA6GameMode::UpdateEachSecond_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::FromInt(CountDownTime));
    AMyGameStateBase* gs = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	gs->CountDownTime = CountDownTime;
}

void AGTA6GameMode::GameOver()
{
	
}


