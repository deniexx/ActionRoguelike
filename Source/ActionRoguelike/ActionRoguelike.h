// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_STAT_GROUP(TEXT("ARG_Game"), STATGROUP_ACTIONRG, STATCAT_Advanced, true, true, true);

static void LogOnScreen(UObject* WorldContext, FString Msg, FColor Color = FColor::White, float Duration = 2.0f)
{
	if (!ensure(WorldContext))
	{
		return;
	}

	const UWorld* World = WorldContext->GetWorld();
	if (!ensure(World))
	{
		return;
	}

	const FString NetPrefix = World->IsNetMode(NM_Client) ? "[Client] " : "[SERVER] ";
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, NetPrefix + Msg);
	}
	
}