// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASDashProjectile::ASDashProjectile()
{
	ExplodeParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticles"));
	ExplodeParticles->SetupAttachment(RootComponent);
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_ProjectileFlight, this, &ASDashProjectile::ProjectileFlight_TimerElapsed, 0.2f);
}

void ASDashProjectile::ProjectileFlight_TimerElapsed()
{
	if (ExplodeParticles)
		ExplodeParticles->ActivateSystem(true);

	MovementComponent->StopMovementImmediately();
	
	GetWorldTimerManager().SetTimer(TimerHandle_WaitForExplode, this, &ASDashProjectile::WaitForExplode_TimerElapsed, 0.2f);
}

void ASDashProjectile::WaitForExplode_TimerElapsed()
{
	APawn* MyInstigator = GetInstigator();
	MyInstigator->SetActorLocation(GetActorLocation());

	Destroy();
}

void ASDashProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	
	GetWorldTimerManager().ClearTimer(TimerHandle_ProjectileFlight);
	GetWorldTimerManager().ClearTimer(TimerHandle_WaitForExplode);

	GetWorldTimerManager().SetTimer(TimerHandle_ProjectileFlight, this, &ASDashProjectile::WaitForExplode_TimerElapsed, 0.2f);

	WaitForExplode_TimerElapsed();
}
