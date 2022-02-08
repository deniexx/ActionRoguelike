// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "RadialForce")
	class URadialForceComponent* RadialForceComponent;
	
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& SweepResult);

};

