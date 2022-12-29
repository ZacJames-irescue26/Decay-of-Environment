// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enums_Structs.h"
#include "Components/BoxComponent.h"
#include "Decay_of_environmentCharacter.h"
#include "TileGrid/CubeGridManager.h"
#include "TileGrid/CubeTile.h"
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
	virtual void BeginPlay() override;
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
	void MoveAI(FVector loc, AActor* a);
	void CanMove();
	bool Canmove = false;
	virtual void OnPossess(APawn* InPawn) override;

private:
	ACubeGridManager* GridManager;
	FTimerHandle ActionRate;
	FTimerHandle MoveRate;
	AActor* previousTarget;
	AActor* targetActor;
	EActionType currentAction;
	UBoxComponent* selectionArea;

	float actionDelay;
	float MoveDelay;
	FVector bbLocation;
	FVector bbExtent;

	UPROPERTY(EditAnywhere, Category = "Lerp")
	float LerpDuration = 3;
	float TimeElapsed = 0;
	float _DeltaTime;
	float Speed = 20;
	FVector characterBBLocation;
	FVector characterBBExtent;
	TArray<ACubeTile*> Path;
	AActor* Actor;
	ADecay_of_environmentCharacter* rtsCharacter;

	bool canPerformActions;
	void CanPerformActions();
	
};
