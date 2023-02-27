// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Timer.h"


UBTDecorator_Timer::UBTDecorator_Timer()
{
	NodeName = "Timer";
}

bool UBTDecorator_Timer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (MyController->canPerformActions)
	{
		return true;
	}
	return false;
}

