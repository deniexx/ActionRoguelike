// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "Kismet/GameplayStatics.h"



void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Please assign BehaviorTree in AI Controller!")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}
