// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enums_Structs.h"
#include "Components/BoxComponent.h"
#include "Decay_of_environmentCharacter.h"
#include "BaseAI.generated.h"

class ADecay_of_environmentCharacter;
class AResource;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API ABaseAI : public AAIController
{
	GENERATED_BODY()
public:
	ABaseAI();
	virtual void Tick(float DeltaTime) override;

	const FString EnumToString(const TCHAR* Enum, int32 EnumValue);
	void DepositeResource();
	void Gather();
	bool FindResource(EResourceType resType, TArray<AActor*> actors);
	void GetNearbyActors(TArray<AActor*>& actors);
	void DamageTarget();
	void AttackTarget(IDamagableInterface* target);
	void GatherResource(IResourceInterface* resource);
	ADecay_of_environmentCharacter* GetRTSCharacter();

	AActor* GetTargetActor() const { return targetActor; }
	void SetTargetActor(AActor* val);
	void MoveAI(FVector loc);
	virtual void OnPossess(APawn* InPawn) override;

private:

	FTimerHandle ActionRate;
	AActor* previousTarget;
	AActor* targetActor;
	EActionType currentAction;
	UBoxComponent* selectionArea;

	float actionDelay;
	FVector bbLocation;
	FVector bbExtent;

	FVector characterBBLocation;
	FVector characterBBExtent;

	ADecay_of_environmentCharacter* rtsCharacter;

	bool canPerformActions;
	void CanPerformActions();
	
};
