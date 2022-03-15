// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_HealSelf.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"

USBTTask_HealSelf::USBTTask_HealSelf()
{
	HealAmount = 50.0f;
}

EBTNodeResult::Type USBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(MyPawn);

		bool Success = AttributeComp->ApplyHealthChange(MyPawn, HealAmount);

		
		return Success ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
