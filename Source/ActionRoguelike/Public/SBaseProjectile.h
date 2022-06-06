// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	// Sets default values for this actor's properties
	ASBaseProjectile();

	UPROPERTY(EditAnywhere, Category = "Stats")
	float LifeSpan;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComponent;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundBase* ExplosionSound;

	UPROPERTY(VisibleAnywhere, Category = "Sounds")
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Particles")
	UParticleSystem* DestroyParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShakeBase;
	

	

public:
	virtual void PostInitializeComponents() override;


protected:
	void Explode(FVector Location);

};
