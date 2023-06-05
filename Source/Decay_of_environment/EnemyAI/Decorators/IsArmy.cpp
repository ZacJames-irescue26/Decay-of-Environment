// Fill out your copyright notice in the Description page of Project Settings.


#include "IsArmy.h"
#include "../EnemyAIController.h"

UIsArmy::UIsArmy()
{
	NodeName = "Is Army";
}

bool UIsArmy::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	// Does the target have resources left
	if (MyController->GetRTSCharacter()->GetStats().unitID != EUnitClass::worker)
	{
		return true;
	}
	return false;
}
