// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTDecorator_IsCollector.h"
#include "../EnemyAIController.h"

UMyBTDecorator_IsCollector::UMyBTDecorator_IsCollector()
{
	NodeName = "IsCollector";
}

bool UMyBTDecorator_IsCollector::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	// Does the target have resources left
	if (MyController->GetRTSCharacter()->GetStats().unitID != 0)
	{
		return false;
	}
	return true;
}
