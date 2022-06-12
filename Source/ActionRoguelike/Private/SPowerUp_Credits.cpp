// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUp_Credits.h"

#include "SPlayerState.h"


ASPowerUp_Credits::ASPowerUp_Credits()
{
	CreditsToAdd = 50;
}

void ASPowerUp_Credits::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn)) return;

	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->AddCredits(CreditsToAdd);
		HideAndCooldownPowerUp();
	}
	
}
