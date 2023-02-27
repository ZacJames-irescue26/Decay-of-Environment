// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../EnemyAIController.h"
#include "BTTask_Timer.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBTTask_Timer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Timer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void CanPerformActions();
	AEnemyAIController* MyController;
};
