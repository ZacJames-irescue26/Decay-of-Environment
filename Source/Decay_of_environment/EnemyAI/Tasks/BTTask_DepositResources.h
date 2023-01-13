// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../../Decay_of_environmentCharacter.h"
#include "BTTask_DepositResources.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBTTask_DepositResources : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_DepositResources();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	AActor* FindClosestBase(ADecay_of_environmentCharacter* Character, TArray<AActor*> _storageActors);
};
