// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Decay_of_environment/UI/BuildingUI.h"
#include "BaseUI.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBaseUI : public UBuildingUI
{
	GENERATED_BODY()
public:
	
	virtual bool Initialize() override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABuildingIcon> BaseToSpawn;
	UFUNCTION()
	void SpawnBase();
	UPROPERTY(meta = (BindWidget))
	class UButton* BuildBaseButton;
};
