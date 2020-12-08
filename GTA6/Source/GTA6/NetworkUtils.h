// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//#include "OnlineSessionSettings.h"

/**
 * 
 */
class GTA6_API NetworkUtils
{
public:
	NetworkUtils();
	~NetworkUtils();

	static bool HostSession();
	static void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
};
