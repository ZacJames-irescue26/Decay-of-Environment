// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInRange.h"
#include "../EnemyAIController.h"
#include "../../Decay_of_environmentCharacter.h"



UBTDecorator_IsInRange::UBTDecorator_IsInRange()
{
	NodeName = "Is In Range";

}

bool UBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	if (MyController->GetTargetActor() != nullptr)
	{
		float minDistance = MyController->bbExtent.GetAbsMax() + MyController->characterBBExtent.GetAbsMax();
		float dist = FVector::Distance(MyController->GetCharacter()->GetActorLocation(), MyController->GetTargetActor()->GetActorLocation());

		if (dist < (minDistance * Character->stats.AttackRange))
		{
			MyController->StopMovement();
			return true;
		}

	}
	return false;
}
