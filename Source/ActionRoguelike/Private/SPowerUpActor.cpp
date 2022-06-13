// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"

#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

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

void ASPowerUpActor::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);

	RootComponent->SetVisibility(bIsActive, true);
}

void ASPowerUpActor::HideAndCooldownPowerUp()
{
	DisableAllActions();
	FTimerHandle EnableActorActions;
	GetWorldTimerManager().SetTimer(EnableActorActions, this, &ASPowerUpActor::EnableActorActions_TimerElapsed, TimerDuration);
}

void ASPowerUpActor::DisableAllActions()
{
	bIsActive = false;
	OnRep_IsActive();
}

void ASPowerUpActor::EnableActorActions_TimerElapsed()
{
	bIsActive = true;
	OnRep_IsActive();
}

FText ASPowerUpActor::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	return FText::GetEmpty();
}

void ASPowerUpActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerUpActor, bIsActive);
}
