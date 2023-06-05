// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionInterfaceWidget.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UMissionInterfaceWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup();
	void Teardown();
};
