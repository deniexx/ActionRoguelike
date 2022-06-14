// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseProjectile.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ASBaseProjectile::ASBaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComponent"));
	EffectComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);

	LifeSpan = 5.0f;

	bReplicates = true;
}

void ASBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SetLifeSpan(LifeSpan);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);

	if (AudioComponent)
		AudioComponent->Play();
}

void ASBaseProjectile::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorLocation());
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShakeBase, GetActorLocation(), 00.0f, 800.0f, 0.0f);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	Destroy();
}

