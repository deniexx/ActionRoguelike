// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUp_Action.h"

#include "SAction.h"
#include "SActionComponent.h"
#include "ActionRoguelike/ActionRoguelike.h"

void ASPowerUp_Action::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn && ActionToGrant)) return;

	USActionComponent* ActionComponent = Cast<USActionComponent>(InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass()));
	if (ActionComponent)
	{
		if (ActionComponent->GetAction(ActionToGrant))
		{
			FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionToGrant));
			LogOnScreen(this, DebugMsg);
			return;
		}

		ActionComponent->AddAction(InstigatorPawn, ActionToGrant);
		HideAndCooldownPowerUp();
	}
}
