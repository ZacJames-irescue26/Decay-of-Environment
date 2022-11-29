// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamagableInterface.h"
#include "Enums_Structs.h"
#include "ResourceInterface.h"
#include "TeamInterface.h"
#include "Decay_of_environmentCharacter.generated.h"

UCLASS(Blueprintable)
class ADecay_of_environmentCharacter : public ACharacter, public IDamagableInterface, public ITeamInterface
{
	GENERATED_BODY()

public:
	ADecay_of_environmentCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

private:

public:
	FORCEINLINE ECharacterType GetType() { return stats.characterType; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "stats")
	FCharacterStats stats;

	virtual int32 GetWeight();
	virtual int32 GetCarryWeight();
	void ClearInventory();
	virtual int32 GetGatherAmount();
	virtual void RecieveResources(int32 amount, IResourceInterface* ri);


	virtual void TakeDamage(float damage) override;
	virtual float GetHealth() override;
	virtual float GetMaxHealth() override;
	virtual FCharacterStats& GetStats();

	virtual int32 GetPlayerTeam() override;
	virtual int32 GetPlayerOwner() override;

};

