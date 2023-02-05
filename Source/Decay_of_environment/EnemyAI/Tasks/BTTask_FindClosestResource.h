// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../../Decay_of_environmentCharacter.h"
#include "../EnemyAIController.h"
#include "BTTask_FindClosestResource.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBTTask_FindClosestResource : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FindClosestResource();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	bool FindResource(EResourceType resType, TArray<AActor*> actors);
	AActor* FindClosestResource(ADecay_of_environmentCharacter* Character, TArray<AActor*> ResourceActors);

	TArray<AActor*> ResourceActors;
	AEnemyAIController* MyController;
};
