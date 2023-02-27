// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "../EnemyAIController.h"
#include "BTDecorator_Timer.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBTDecorator_Timer : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:

	UBTDecorator_Timer();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	void CanPerformActions();
	

};
