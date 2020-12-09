// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverBoardBase.h"


#include "GTA6Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "MyPlayerState.h"

class AMyPlayerState;

void UGameOverBoardBase::BeginPlay()
{
	/*TArray<AActor*> FindResults;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerState::StaticClass(), FindResults);*/
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("GameOverBoard!"));
	TArray<APlayerState*> AllPlaerStates = GetWorld() -> GetGameState() -> PlayerArray;
	for (auto it : AllPlaerStates)
	{
		AMyPlayerState* ps = Cast<AMyPlayerState>(it);

		AddLine(ps->KillNum, ps->DeathNum, ps->PlayerName);// ps->GetPlayerName();ps->SetPlayerName() GetPlayerName()
	}
}

void UGameOverBoardBase::AddLine(int32 KillNum, int32 DeathNum, FString PlayerName)
{
}
