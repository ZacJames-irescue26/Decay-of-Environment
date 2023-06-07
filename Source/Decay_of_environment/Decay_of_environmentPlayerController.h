// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include <Components/BoxComponent.h>
#include "Decay_of_environmentCharacter.h"
#include "Overseerer.h"
#include "ResourceInterface.h"
#include "DamagableInterface.h"
#include "CharacterDetails.h"
#include "Net/UnrealNetwork.h"
#include "Building.h"
#include <Components/WidgetSwitcher.h>
#include "Abilities/AbilityManager.h"
#include "MissionManager.h"
#include "MissionDataAsset.h"
#include "Decay_of_environmentPlayerController.generated.h"



/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class ADecay_of_environmentPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	ADecay_of_environmentPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
	FVector MousePos;
	bool leftMouseDown; // Input is bring pressed
	bool RightMouseDown;
	void Test();
	UFUNCTION(Client, Reliable)
	void MoveUnits(FVector loc);
	AOverseerer* GetOverseerer();
	TArray<ADecay_of_environmentCharacter*>& GetUnitsArray() {return selectedUnits;};
	double MouseStartX;
	double MouseStartY;
	double MouseEndX;
	double MouseEndY;

	void SpawnBuilding();
	void SpawnUnit();

	void Shield();
	void DashAbility();
	UMissionDataAsset* GetMissionDataAsset();
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> BuildingToSpawn;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> UnitToSpawn;
	
	/*UPROPERTY(EditAnywhere)
	TSubclassOf<AShieldAblitity> AbilityToSpawn;*/

	/*UPROPERTY(EditAnywhere)
	TSubclassOf<ADash> Dash;*/
	UPROPERTY(EditAnywhere)
	class UWidgetSwitcher* AbilitySwitcher;
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	// AMissionManager* GetMissionManager();
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

	void AttackTarget(IDamagableInterface* target);
	void Moveattack();
	void RightClick();
	void RightClickReleased();
	void GatherResources(IResourceInterface* res);

	void Build(class AUnbuiltBuilding* Building);
	ITeamInterface* GetTeam(AActor* other);
	IResourceInterface* GetResource(AActor* other);
	void ZoomIn();
	void ZoomOut();
	IDamagableInterface* GetDamagable(AActor* other);

	void Button1();
	void Button2();
	void Button3();
private:
	
	void SelectUnits();
	

private:
	AAbilityManager* AbilityManager;
	float MaxZoom; 
	float MinZoom;
	float ZoomRate;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed

	FVector centerMouseLocation;
	float dist;

	UBoxComponent* selectionArea;
	FVector selectionSize;
	AOverseerer* overseerer;
	FVector mouseStart;
	FVector mouseEnd;
	FHitResult hit;
	FVector _Location;
	double LocationX;
	double LocationY;
	TArray<ABuilding*> Buildings;
	TArray<AActor*> ActorBuildings;

	TMap<int, TArray<ADecay_of_environmentCharacter*>> ControlGroupMap;
	TArray<ADecay_of_environmentCharacter*> selectedUnits;
	TSubclassOf<UUserWidget> characterUItemplate;
	UCharacterDetails* characterUI;

	TSubclassOf<class UUserWidget> UserInterfaceClass;
	class UUserInterface* UserInterface;
};


