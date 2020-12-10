// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverLineBase.h"

void UGameOverLineBase::InitLineInfo(int32 Kill_, int32 Death_, FString& PlayerName)
{
	Kill = Kill_;
	Death = Death_;
	ThePlayerName = PlayerName;
}
