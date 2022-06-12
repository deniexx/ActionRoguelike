// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpActor.h"
#include "SPowerUp_Action.generated.h"

class USAction;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerUp_Action : public ASPowerUpActor
{
	GENERATED_BODY()

public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	TSubclassOf<USAction> ActionToGrant;
};
