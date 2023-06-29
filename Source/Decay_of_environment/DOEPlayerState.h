// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DOEPlayerState.generated.h"

//USTRUCT(BlueprintType)
//struct FStatistics
//{
//	GENERATED_USTRUCT_BODY()
//public:
//	UPROPERTY(EditAnywhere)
//	int32 ComponentsValue = 100;
//	
//	int32 UnitsKilled = 0;
//	int32 SpecialUnitsKilled = 0;
//	int32 ProtectObjectivesDestroyed = 0;
//	int32 ObjectivesReachDestination = 0;
//	int32 protectObjectiveGoal = 3;
//
//};
/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API ADOEPlayerState : public APlayerState
{
	GENERATED_BODY()
private:
	

public:
	UFUNCTION(Server, Reliable)
	void Server_SetPlayerOwner(int Player);
protected:
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	FORCEINLINE void SetPlayerOwner(int _Owner) {PlayerOwner = _Owner;}

	FORCEINLINE int GetTeam() { return Team; }
	FORCEINLINE int GetPlayerOwner() { return PlayerOwner; }
	UPROPERTY(EditAnywhere, Replicated)
	int Team;
	UPROPERTY(EditAnywhere, Replicated)
	int PlayerOwner;
	UPROPERTY(EditAnywhere, Replicated)
	int BaseNumber = 1;
	UPROPERTY(EditAnywhere, Replicated)
	int BarracksNumber = 0;
	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<class ABuilding*> OwnedBuildingArray;
	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<class ADecay_of_environmentCharacter*> OwnedUnitArray;


};
