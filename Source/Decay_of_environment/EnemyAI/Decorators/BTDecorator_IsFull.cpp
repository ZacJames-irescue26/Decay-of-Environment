// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsFull.h"
#include "../../Decay_of_environmentCharacter.h"
#include "../EnemyAIController.h"

UBTDecorator_IsFull::UBTDecorator_IsFull()
{

}

bool UBTDecorator_IsFull::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	if ((MyController->GetRTSCharacter()->GetCarryWeight() - MyController->GetRTSCharacter()->GetWeight()) <= 0)
	{
		return false;
	}
	return true;
}
