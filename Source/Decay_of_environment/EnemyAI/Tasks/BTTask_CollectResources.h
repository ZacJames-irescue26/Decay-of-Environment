// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../../Enums_Structs.h"
#include "BTTask_CollectResources.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBTTask_CollectResources : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_CollectResources();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	bool FindResource(EResourceType resType, TArray<AActor*> actors);
};
