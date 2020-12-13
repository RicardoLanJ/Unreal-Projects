// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

#include "Net/UnrealNetwork.h"

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameStateBase, CountDownTime);
}

//void AMyGameStateBase::OnRep_CountDownTime()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "update");
//}


