// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "MyGameInstance.h"

AMyPlayerState::AMyPlayerState()
{
	//InitPlayerInfo("123");
}

void AMyPlayerState::BeginPlay()
{
	UMyGameInstance* GIRef = Cast<UMyGameInstance>(GetGameInstance());
	InitPlayerInfo(GIRef->PlayerName);
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, KillNum);
	DOREPLIFETIME(AMyPlayerState, DeathNum);
	DOREPLIFETIME(AMyPlayerState, ThePlayerName);
}

void AMyPlayerState::AddOneDeathNum()
{
	DeathNum++;
}

void AMyPlayerState::AddKillNum(int32 kills)
{
	KillNum += kills;
}

void AMyPlayerState::InitPlayerInfo_Implementation(const FString& PlayerName_)
{
	ThePlayerName = PlayerName_;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, ThePlayerName);
}