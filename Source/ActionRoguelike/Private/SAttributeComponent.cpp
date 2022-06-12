// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "Net/UnrealNetwork.h"
#include "SGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("sc.DamageMultiplier"), 1.0f, TEXT("Global Damage Multiplier for Attribute Component"), ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	MaxHealth = 100.0f;
	Health = MaxHealth;

	RageMax = 100.0f;
	Rage = RageMax;

	SetIsReplicatedByDefault(true);
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f) return false;

	if (Delta < 0.0f)
	{
		const float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}
	
	const float OldHealth = Health;
	const float NewHealth = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	const float ActualDelta = NewHealth - OldHealth;

	if (GetOwner()->HasAuthority())
	{
		Health = NewHealth;

		if (ActualDelta != 0)
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);

		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}
	
	return ActualDelta != 0;
}

bool USAttributeComponent::ApplyRage(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f) return false;
	
	const float OldRage = Rage;
	const float NewRage = FMath::Clamp(Rage + Delta, 0.0f, RageMax);

	const float ActualDelta = NewRage - OldRage;

	if (GetOwner()->HasAuthority())
	{
		Rage = NewRage;

		if (ActualDelta != 0)
			MulticastRageChanged(InstigatorActor, Rage, ActualDelta);
	}
	
	return ActualDelta != 0;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::Kill(AActor* Instigator)
{
	return ApplyHealthChange(Instigator, -GetHealthMax());
}

bool USAttributeComponent::IsAtMaxHealth()
{
	return Health == MaxHealth;
}

float USAttributeComponent::GetHealthMax()
{
	return MaxHealth;
}

float USAttributeComponent::GetHealth()
{
	return Health;
}

float USAttributeComponent::GetRage()
{
	return Rage;
}

float USAttributeComponent::GetRageMax()
{
	return RageMax;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

void USAttributeComponent::MulticastRageChanged_Implementation(AActor* InstigatorActor, float NewRage, float Delta)
{
	OnRageChanged.Broadcast(InstigatorActor, this, NewRage, Delta);
}

void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAttributeComponent, Health);
	DOREPLIFETIME(USAttributeComponent, MaxHealth);
}

