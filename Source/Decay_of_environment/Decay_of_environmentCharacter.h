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

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UDecalComponent* Decal;
	USphereComponent* CollisionSphere;
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
	virtual void SetPlayerTeam(int32 Value) override;
	virtual void SetPlayerOwner(int32 Value) override;
	

	//template <typename T>
	//static FORCEINLINE T* LoadObjFromPath(const FName& Path)
	//{
	//	if (Path == NAME_None)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Failed to load texture")); 
	//		return nullptr;
	//	}
	//	return Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *Path.ToString()));
	//}

	//static FORCEINLINE UMaterial* LoadMaterialFromPath(const FName& Path)
	//{
	//	if (Path == NAME_None)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("Failed to load texture"));
	//		return nullptr;
	//	}
	//	return LoadObjFromPath<UMaterial>(Path);
	//}
	
};

