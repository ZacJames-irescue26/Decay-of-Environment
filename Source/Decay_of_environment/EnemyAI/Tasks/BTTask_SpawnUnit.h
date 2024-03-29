// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../../Decay_of_environmentCharacter.h"
#include "BTTask_SpawnUnit.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBTTask_SpawnUnit : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_SpawnUnit();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADecay_of_environmentCharacter> UnitToSpawn;

	
	class ADecay_of_environmentCharacter* EnemyUnit;
};
