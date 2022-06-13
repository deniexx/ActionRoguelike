// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPowerUpActor.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASPowerUpActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUpActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;

	UPROPERTY(ReplicatedUsing="OnRep_IsActive")
	bool bIsActive;

	UFUNCTION()
	void OnRep_IsActive();

	UFUNCTION(BlueprintCallable, Category = "PowerUps")
	void HideAndCooldownPowerUp();
	
	void DisableAllActions();

	void EnableActorActions_TimerElapsed();

	virtual FText GetInteractText_Implementation(APawn* InstigatorPawn) override;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float TimerDuration;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float HealAmount;

};
