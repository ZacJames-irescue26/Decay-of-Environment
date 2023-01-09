// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Decay_of_environmentCharacter.h"
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "../Building.h"
#include "../RTSGameInstance.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	TSubclassOf<class ADecay_of_environmentCharacter> UnitClass;
	URTSGameInstance* GameInstance;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowprivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviourTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowprivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviourTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowprivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;


};
