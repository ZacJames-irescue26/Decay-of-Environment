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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Tick(float DeltaTime) override;
	//UFUNCTION()
	//void OnRep_TargetActor();
	UFUNCTION(NetMulticast, Reliable)
	void AIbehaviour();

	virtual void BeginPlay() override;
	const FString EnumToString(const TCHAR* Enum, int32 EnumValue);
	void DepositeResource();
	void Gather();
	bool FindResource(EResourceType resType, TArray<AActor*> actors);
	void GetNearbyActors(TArray<AActor*>& actors);
	void Patrol(FVector Location, AActor* c);
	void AttackMove();
	void Build(class AUnbuiltBuilding* _Building);
	void BuildBuilding();
	UFUNCTION(Server, Reliable)
	void DamageTarget();
	UFUNCTION(Server, Reliable)
	void AttackTarget(AActor* target);
	void GatherResource(AActor* resource);
	ADecay_of_environmentCharacter* GetRTSCharacter();
	AActor* GetTargetActor() const { return targetActor; }
	UFUNCTION(server, Reliable)
	void SetTargetActor(AActor* val);
	UFUNCTION(Server, Reliable)
	void ServerSetTargetActor(AActor* val);
	UFUNCTION(Client, Reliable)
	void ClientSetTargetActor(AActor* val);
	UFUNCTION(NetMulticast, Reliable)
	void MoveAI(FVector loc, AActor* a);
	void CanMove();
	bool Canmove = false;
	virtual void OnPossess(APawn* InPawn) override;

private:
	ACubeGridManager* GridManager;
	FTimerHandle ActionRate;
	FTimerHandle MoveRate;
	UPROPERTY(Replicated)
	AActor* previousTarget;
	UPROPERTY(Replicated)
	AActor* targetActor;
	UPROPERTY(Replicated)
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
	float Speed = 100;
	int i = 0;
	FVector characterBBLocation;
	FVector characterBBExtent;
	TArray<ACubeTile*> Path;
	AActor* Actor;
	ADecay_of_environmentCharacter* rtsCharacter;
	bool canPerformActions;
	void CanPerformActions();

	bool Building = false;
	
};
