// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Decay_of_environment/UI/BuildingUI.h"
#include "BarracksUI.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBarracksUI : public UBuildingUI
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	UFUNCTION()
	void SpawnBarracks();
	UPROPERTY(meta = (BindWidget))
	class UButton* BuildBarracksButton;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABuildingIcon> BarracksToSpawn;
};
