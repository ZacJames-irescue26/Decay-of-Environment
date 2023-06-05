// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "Components/HorizontalBox.h"
#include "MissionSelectIcon.h"
#include "MissionInterfaceWidget.h"
#include "MissionSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UMissionSelectWidget : public UMissionInterfaceWidget
{
	GENERATED_BODY()
public:
	UMissionSelectWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* MissionSelectBox;

	TSubclassOf<class UMissionSelectIcon> MissionIconClass;

	void MissionBoxUpdate();
};
