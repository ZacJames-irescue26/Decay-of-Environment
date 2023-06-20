// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Decay_of_environment/UI/BuildingUI.h"
#include "RadarUI.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API URadarUI : public UBuildingUI
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	UFUNCTION()
	void SpawnRadar();
	UPROPERTY(meta = (BindWidget))
	class UButton* BuildRadarButton;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABuildingIcon> RadarToSpawn;
};
