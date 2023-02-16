// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsTargetAlly.h"
#include "../EnemyAIController.h"
#include "../../Decay_of_environmentCharacter.h"
UBTDecorator_IsTargetAlly::UBTDecorator_IsTargetAlly()
{
	NodeName = TEXT("Is Target Ally");
}

bool UBTDecorator_IsTargetAlly::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	if (MyController->GetTargetActor() == nullptr)
	{
		return false;
	}
	ADecay_of_environmentCharacter* TargetActor = Cast<ADecay_of_environmentCharacter>(MyController->GetTargetActor());
	if (Character->stats.team != TargetActor->stats.team)
	{
		return true;
	}
	return false;
}
