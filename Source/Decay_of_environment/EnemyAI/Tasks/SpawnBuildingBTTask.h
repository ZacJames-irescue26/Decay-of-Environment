// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../../Building.h"
#include "SpawnBuildingBTTask.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API USpawnBuildingBTTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	USpawnBuildingBTTask();
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> BuildingToSpawn;
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
