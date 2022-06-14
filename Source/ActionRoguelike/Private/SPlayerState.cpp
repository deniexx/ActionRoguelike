// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "SSaveGame.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"


int32 ASPlayerState::GetCredits() const
{
	return Credits;
}

void ASPlayerState::AddCredits(int32 Delta)
{
	if (!ensure(Delta > 0.0f)) return;
	
	Credits += Delta;
	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool ASPlayerState::RemoveCredits(int32 Delta)
{
	if (!ensure(Delta > 0.0f))
	{
		return false;
	}

	if (Credits < Delta)
	{
		UE_LOG(LogTemp, Warning, TEXT("Credits: %d, Delta: %d"), Credits, Delta);
		return false;
	}
	
	Credits -= Delta;
	OnCreditsChanged.Broadcast(this, Credits, Delta);
	
	return true;
}

void ASPlayerState::OnRep_Credits(int32 OldCredits)
{
	OnCreditsChanged.Broadcast(this, Credits, Credits - OldCredits);
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPlayerState, Credits);
}


// ------------------------------------ SAVE GAME ------------------------------------ //
void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credits = Credits;
	}
}

void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		AddCredits(SaveObject->Credits);
	}
}
