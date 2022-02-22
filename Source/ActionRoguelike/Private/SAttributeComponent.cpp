// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	MaxHealth = 100.0f;
	Health = MaxHealth;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	const float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	const float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return ActualDelta != 0;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::IsAtMaxHealth()
{
	return Health == MaxHealth;
}

