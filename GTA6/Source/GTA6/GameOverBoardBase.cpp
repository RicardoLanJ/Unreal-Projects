// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverBoardBase.h"

#include <string>



#include "GameOverLineBase.h"
#include "GTA6Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "MyPlayerState.h"
#include "Components/ScrollBox.h"

class AMyPlayerState;

void UGameOverBoardBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	/*TArray<AActor*> FindResults;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerState::StaticClass(), FindResults);*/
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("GameOverBoard!"));
	TArray<APlayerState*> AllPlaerStates = GetWorld()->GetGameState()->PlayerArray;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::FromInt(AllPlaerStates.Num()));
	for (auto it : AllPlaerStates)
	{
		AMyPlayerState* ps = Cast<AMyPlayerState>(it);

		AddLine(ps->KillNum, ps->DeathNum, ps->ThePlayerName);// ps->GetPlayerName();ps->SetPlayerName() GetPlayerName()
	}
}

void UGameOverBoardBase::AddLine(int32 KillNum, int32 DeathNum, FString PlayerName)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::FromInt(KillNum) + FString::FromInt(DeathNum) + PlayerName);
	UScrollBox* ScrollBox = Cast<UScrollBox>(GetWidgetFromName("ScrollBox_52"));
	UClass* LineClass = LoadClass<UUserWidget>(NULL, TEXT("/Game/ThirdPerson/GameOverLine.GameOverLine_C"));
	if (LineClass == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "find bu dao......");
	}
	else
	{
		UGameOverLineBase* Line = CreateWidget<UGameOverLineBase>(this, LineClass);
		Line->InitLineInfo(KillNum, DeathNum, PlayerName);
		ScrollBox->AddChild(Line);
	}
	/*FStringClassReference LineClassRef(TEXT("Game/ThirdPerson/ScoreLine"));
	UClass* LineClass = LineClassRef.TryLoadClass<UUserWidget>();*/
	//static ConstructorHelpers::FClassFinder<UUserWidget> LineBPClass(TEXT("Game/ThirdPerson/ScoreLine"));
	/*if (LineBPClass.Class != NULL)
	{
		UUserWidget* Line = CreateWidget<UUserWidget>(this, LineBPClass.Class);
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "wrong bp");
	}*/
	//ScrollBox_52->AddChild(Line);
}
