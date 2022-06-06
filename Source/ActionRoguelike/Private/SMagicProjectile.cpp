// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SGameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	Damage = 20.0f;
}


void ASMagicProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	ApplyDamageAndDestroyActor(Other, Hit);
}

/*
void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ApplyDamageAndDestroyActor(OtherActor, SweepResult);
}
*/

void ASMagicProjectile::ApplyDamageAndDestroyActor(AActor* OtherActor, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, Hit);
		
		Explode(Hit.ImpactPoint);
	}
}
