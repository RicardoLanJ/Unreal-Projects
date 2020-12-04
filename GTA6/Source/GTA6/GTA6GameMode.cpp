// Copyright Epic Games, Inc. All Rights Reserved.

#include "GTA6GameMode.h"
#include "GTA6Character.h"
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
