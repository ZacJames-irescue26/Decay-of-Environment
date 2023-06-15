// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" 
#include "Components/GridPanel.h"

#include "Components/ScrollBox.h"
#include "UserInterfaceWidget.h"
#include <Components/Button.h>
#include <Engine/World.h>

#include "../Decay_of_environmentPlayerController.h"
#include "../Building.h"
#include <Components/TextBlock.h>
#include "Components/Image.h"
#include <Components/HorizontalBox.h>
#include <Components/WidgetSwitcher.h>
#include <Components/Widget.h>
#include "../Abilities/ShieldAblitity.h"
#include "../Abilities/Dash.h"
#include <Components/VerticalBox.h>
#include "MissionWidget.h"
#include "UserInterface.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UUserInterface : public UUserInterfaceWidget
{
	GENERATED_BODY()
public:
	UUserInterface(const FObjectInitializer& ObjectInitializer);
	void UpdateText();

	void Mission();
	inline UWidgetSwitcher* GetAbilitySwitcher() { return AbilitySwitcher; }

	/*////////////////Abilities//////////////////////////*/
	void SwitchAbilities(UWidget* Widget);
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* AbilitySwitcher;
	UPROPERTY(meta = (BindWidget))
	class UWidget* WorkerAbilities;
	UPROPERTY(meta = (BindWidget))
	class UWidget* ArmyAbilities;
	UPROPERTY(meta = (BindWidget))
	class UButton* Ability1;
	UPROPERTY(meta = (BindWidget))
	class UButton* Ability2;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MissionBox;

	UMissionWidget* mission;
protected:
	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UGridPanel* UnitGridPanel;
	
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* UnitScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* BuildingButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* UnitButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ComponentsValue;

	UPROPERTY(meta = (BindWidget))
	class UImage* AbilityImage;

	/*UPROPERTY(meta = (BindWidget))
	class */
	
		
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADash> Dash;

	UWidgetAnimation* TaskComplete;

	UFUNCTION()
	void SpawnBuilding();

	UFUNCTION()
	void SpawnUnit();

	UFUNCTION()
	void Button1();

	UFUNCTION()
	void Button2();


	
	TSubclassOf<class UMissionWidget> MissionClass;

	ADecay_of_environmentPlayerController* PlayerController;
	UWorld* World;
	
	bool IsPlayed = false;

};
