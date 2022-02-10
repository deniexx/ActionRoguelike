// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

	ASDashProjectile();
	
protected:

	UPROPERTY(EditAnywhere, Category = "Particles")
	UParticleSystemComponent* ExplodeParticles;
	
	FTimerHandle TimerHandle_ProjectileFlight;
	FTimerHandle TimerHandle_WaitForExplode;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void ProjectileFlight_TimerElapsed();

	UFUNCTION()
	void WaitForExplode_TimerElapsed();

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
