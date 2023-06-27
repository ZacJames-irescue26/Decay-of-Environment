// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Decay_of_environment/UI/BuildingUI.h"
#include "BuilderUI.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBuilderUI : public UBuildingUI
{
	GENERATED_BODY()
	public:
	virtual bool Initialize() override;
	UFUNCTION()
	void SpawnBuilder();
	UPROPERTY(meta = (BindWidget))
	class UButton* BuildBuilderButton;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADecay_of_environmentCharacter> BuilderToSpawn;
};
