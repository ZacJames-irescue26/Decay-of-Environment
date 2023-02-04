// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../../Decay_of_environmentCharacter.h"
#include "BTTask_FindBase.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBTTask_FindBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FindBase();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	AActor* FindClosestBase(ADecay_of_environmentCharacter* Character, TArray<AActor*> _storageActors);
};
