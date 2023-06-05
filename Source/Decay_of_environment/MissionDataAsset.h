// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MissionDataAsset.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	CollectResources,
	killUnits,
	DestroyObjective,
	ProtectObjective

};

USTRUCT(BlueprintType)
struct FMission
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Missions")
	FString Mission;
	UPROPERTY(EditAnywhere, Category = "Missions")
	FString MissionText;
	UPROPERTY(EditAnywhere, Category = "Missions")
	int MissionObjective;
	UPROPERTY(EditAnywhere, Category = "Missions")
	EObjectiveType Objectivetype;
	

};
/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UMissionDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Missions")
	TMap<FString, FMission> MissionMap;
};
