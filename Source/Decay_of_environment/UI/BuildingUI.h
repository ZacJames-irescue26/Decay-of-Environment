// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingUI.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UBuildingUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UBuildingUI(const FObjectInitializer& ObjectInitializer);
	//class ADecay_of_environmentPlayerController* PlayerController;
};
