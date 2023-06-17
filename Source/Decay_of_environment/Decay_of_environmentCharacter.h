// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamagableInterface.h"
#include "Enums_Structs.h"
#include "ResourceInterface.h"
#include "TeamInterface.h"
#include <Components/DecalComponent.h>
#include <Components/SphereComponent.h>
#include "Decay_of_environmentCharacter.generated.h"

//USTRUCT(BlueprintType)
//struct FUnitAbilities
//{
//	GENERATED_USTRUCT_BODY()
//public:
//	int32 Ability_One = 0;
//	int32 Ability_Two = 0;
//	int32 Abiltiy_Three = 0;
//	int32 Ability_Four = 0;
//};

UCLASS(Blueprintable)
class ADecay_of_environmentCharacter : public ACharacter, public IDamagableInterface, public ITeamInterface
{
	GENERATED_BODY()

public:
	ADecay_of_environmentCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION(Server, Reliable)
	void DestroyCharacter();
	
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UDecalComponent* Decal;
	USphereComponent* CollisionSphere;
private:

public:
	FORCEINLINE ECharacterType GetType() { return stats.characterType; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "stats", Replicated)
	FCharacterStats stats;
	virtual int32 GetWeight();
	virtual int32 GetCarryWeight();
	void ClearInventory();
	virtual int32 GetGatherAmount();
	virtual void RecieveResources(int32 amount, IResourceInterface* ri);

	
	virtual void TakeDamage(float damage) override;
	UFUNCTION(Server, Reliable)
	virtual void Server_TakeDamage(float damage) override;
	virtual float GetHealth() override;
	virtual float GetMaxHealth() override;
	virtual FCharacterStats& GetStats();

	virtual int32 GetPlayerTeam() override;
	virtual int32 GetPlayerOwner() override;
	virtual void SetPlayerTeam(int32 Value) override;
	virtual void SetPlayerOwner(int32 Value) override;
	
	virtual void DestroyUnit();
	void SetupMissionWaypoints();
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	TArray<FVector> Waypoints;
	UPROPERTY(EditAnywhere)
	int32 WaypointCounter;

	bool canAttack = true;
	bool canPerformActions = true;
	FTimerHandle ActionRate;
	float actionDelay = 0.5f;
	class ADecay_of_environmentPlayerController* m_PlayerController;
	
};

