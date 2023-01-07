// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyBTTaskRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UEnemyBTTaskRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UEnemyBTTaskRandomLocation();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "search", meta = (AllowPrivateAccess = true))
	float SearchRadius{500.0f};
};
