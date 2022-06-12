// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

	HealAmount = 50.0f;
	TimerDuration = 20.0f;

	SetReplicates(true);
}

void ASPowerUpActor::HideAndCooldownPowerUp()
{
	DisableAllActions();
	FTimerHandle EnableActorActions;
	GetWorldTimerManager().SetTimer(EnableActorActions, this, &ASPowerUpActor::EnableActorActions_TimerElapsed, TimerDuration);
}

void ASPowerUpActor::DisableAllActions()
{
	SetActorEnableCollision(false);
	BaseMesh->SetVisibility(false);
}

void ASPowerUpActor::EnableActorActions_TimerElapsed()
{
	SetActorEnableCollision(true);
	BaseMesh->SetVisibility(true);
}
