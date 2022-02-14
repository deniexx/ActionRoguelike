// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

	HealAmount = 50.0f;
	TimerDuration = 20.0f;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComponent && !AttributeComponent->IsAtMaxHealth())
		{
			AttributeComponent->ApplyHealthChange(HealAmount);
			DisableAllActions();
			FTimerHandle EnableActorActions;
			GetWorldTimerManager().SetTimer(EnableActorActions, this, &ASHealthPotion::EnableActorActions_TimerElapsed, TimerDuration);
		}
	}
}

void ASHealthPotion::DisableAllActions()
{
	SetActorEnableCollision(false);
	BaseMesh->SetVisibility(false);
}

void ASHealthPotion::EnableActorActions_TimerElapsed()
{
	SetActorEnableCollision(true);
	BaseMesh->SetVisibility(true);
}





