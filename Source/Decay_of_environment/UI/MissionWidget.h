// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "MissionWidget.generated.h"

USTRUCT(BlueprintType)
struct FMission
{
	GENERATED_USTRUCT_BODY()
public:
	FString MissionText;
	int MissionObjective;

};
/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UMissionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MissionText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MissionProgress;

	TMap<FString, FMission> MissionMap;
	void SetupMissions();

};
