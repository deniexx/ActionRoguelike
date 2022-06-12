// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"
#include "SActionComponent.h"
#include "Net/UnrealNetwork.h"
#include "ActionRoguelike/ActionRoguelike.h"

void USAction::Initialize(USActionComponent* NewActionComponent)
{
	ActionComponent = NewActionComponent;
}

void USAction::StartAction_Implementation(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;
	
	UE_LOG(LogTemp, Log, TEXT("Running %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	RepData.bIsRunning = false;
	RepData.Instigator = Instigator;
	
	UE_LOG(LogTemp, Log, TEXT("Stopping %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::White);
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning()) return false;
	
	const USActionComponent* Comp = GetOwningComponent();
	
	if(Comp->ActiveGameplayTags.HasAnyExact(BlockedTags))
	{
		return false;
	}

	return true;
}

bool USAction::IsRunning() const
{
	return RepData.bIsRunning;
}

UWorld* USAction::GetWorld() const
{
	const AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}

	return nullptr;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return ActionComponent;
}

void USAction::OnRep_RepData()
{
	if (RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StopAction(RepData.Instigator);
	}
}

void USAction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAction, RepData);
	DOREPLIFETIME(USAction, ActionComponent);
}
