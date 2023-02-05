// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StopMovement.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBTTask_StopMovement : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_StopMovement();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
