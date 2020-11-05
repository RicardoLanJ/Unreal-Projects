// Fill out your copyright notice in the Description page of Project Settings.

#include "MySaveGame.h"

bool UMySaveGame::AddRecord(const FName& name, int32 score)
{
    for (int i = 0; i < rank.Num(); ++i) {
        FRecord&record = rank[i];
        if (record.score < score) {
            rank.Insert(FRecord{name,score }, i);
            rank.RemoveAt(rank.Num() - 1);
            return true;
        }
    }
    return false;
}

UMySaveGame::UMySaveGame()
{
    FRecord tmp(TEXT("-"), 0 );
    rank.Init(tmp, 10);
}