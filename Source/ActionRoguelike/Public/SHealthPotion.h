// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SHealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	void DisableAllActions();

	void EnableActorActions_TimerElapsed();

	UPROPERTY(EditAnywhere, Category = "Stats")
	float TimerDuration;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float HealAmount;
};
