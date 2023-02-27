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
	ADecay_of_environmentCharacter* rtsCharacter;
	ADecay_of_environmentCharacter* GetRTSCharacter();
	void SetTargetActor(AActor* val);
	AActor* GetTargetActor() const { return targetActor; }
	TSubclassOf<class ADecay_of_environmentCharacter> UnitClass;
	URTSGameInstance* GameInstance;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowprivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviourTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowprivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviourTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowprivateAccess = true))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

public:

	AActor* previousTarget;
	AActor* targetActor;
	
	FVector characterBBLocation;
	FVector characterBBExtent;

	FVector bbLocation;
	FVector bbExtent;
	
	bool canAttack = true;
	bool canPerformActions = true;
	FTimerHandle ActionRate;
	float actionDelay = 0.5f;
	//float actionRate = 0.5;
};
