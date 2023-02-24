// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "../MissionManager.h"
#include <Components/ProgressBar.h>
#include <Components/WidgetSwitcher.h>
#include "MissionWidget.generated.h"

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

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MissionText_1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MissionProgress_1;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MissionGraphicsSwitcher;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ComponentProgressBar;
};
