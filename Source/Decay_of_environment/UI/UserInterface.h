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

	UFUNCTION()
	void SpawnBuilding();

	UFUNCTION()
	void SpawnUnit();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> BuildingToSpawn;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> UnitToSpawn;
	ADecay_of_environmentPlayerController* PlayerController;
	UWorld* World;

	TArray<ABuilding*> Buildings;
	TArray<AActor*> ActorBuildings;

};
