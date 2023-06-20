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

	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Test();
	UFUNCTION(Server, Reliable)
	void MoveUnits(FVector loc);
	AOverseerer* GetOverseerer();
	TArray<ADecay_of_environmentCharacter*>& GetUnitsArray() {return selectedUnits;};
	
	UFUNCTION(Server, Reliable)
	void SpawnBuilding(TSubclassOf<class ABuildingIcon> IconToSpawn);
	UFUNCTION(Server, Reliable)
	void Server_DestroyBuildingIcon(ABuildingIcon* IconToDestroy);
	void SpawnUnit();
	void SelectUnits();
	void AttackTarget(IDamagableInterface* target);
	void GatherResources(IResourceInterface* res);
	
	UFUNCTION(Server, Reliable)
	void Server_AttackTarget(AActor* target, ADecay_of_environmentCharacter* c);
	UFUNCTION(Server, Reliable)
	void Server_GatherResources(AActor* res, ADecay_of_environmentCharacter* c);
	UFUNCTION(Server, Reliable)
	void Server_SelectUnits(ADecay_of_environmentCharacter* _character);
	UFUNCTION(Server, Reliable)
	void Server_SelectBuilding(class ABuilding* _Building);
	UFUNCTION(Server, Reliable)
	void Server_SpawnBuilding(FVector location, FRotator rotation);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnBuilding(FVector location, FRotator rotation);
	
	void SpawnUnBuiltBuilding(FVector location, FRotator rotation, class ABuildingIcon* IconToDestroy);
	void SpawnBuiltBuilding(FVector location, FRotator rotation, AUnbuiltBuilding* BuildingToDestroy);
	UFUNCTION(Server, Reliable)
	void Server_SpawnBuiltBuilding(FVector location, FRotator rotation);
	UFUNCTION(Server, Reliable)
	void Server_DestroyUnbuiltBuilding(AUnbuiltBuilding* BuildingToDestroy);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnBuiltBuilding(FVector location, FRotator rotation);
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DestroyUnbuiltBuilding(AUnbuiltBuilding* BuildingToDestroy);
	void Shield();
	void DashAbility();
	UMissionDataAsset* GetMissionDataAsset();
	void CalculateUnitsInsideBox(FVector2D startPos, FVector2D EndPos, TArray<AActor*> SelectedUnits);
	void singleClick(AActor* actor);
	class ADOEPlayerState* DOEPlayerState;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABuildingIcon> BuildingIconToSpawn;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUnbuiltBuilding> UnbuiltBuildingToSpawn;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABuilding> BuildingToSpawn;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> UnitToSpawn;

	UPROPERTY(EditAnywhere)
	class UWidgetSwitcher* AbilitySwitcher;
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	UFUNCTION(Server, Reliable)
	void Server_UpdatePlayerOwner();
	virtual void BeginPlay() override;
	// AMissionManager* GetMissionManager();
	virtual void SetupInputComponent() override;

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	FVector2D P2minusP1(FVector2D p1, FVector2D p2);
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);
	void Moveattack();
	void RightClick();
	void RightClickReleased();


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
	UPROPERTY(Replicated)
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
	UPROPERTY(Replicated)
	TArray<ADecay_of_environmentCharacter*> selectedUnits;
	ABuilding* SeletedBuilding;
	TSubclassOf<UUserWidget> characterUItemplate;
	UCharacterDetails* characterUI;

	TSubclassOf<class UUserWidget> UserInterfaceClass;
	class UUserInterface* UserInterface;
public:
	double MouseStartX;
	double MouseStartY;
	double MouseEndX;
	double MouseEndY;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
	FVector MousePos;
	bool leftMouseDown; // Input is bring pressed
	bool RightMouseDown;
	UPROPERTY(Replicated)
	AActor* targetFound;
	UPROPERTY(Replicated)
	class AUnbuiltBuilding* m_UnBuiltBuilding;
	class ABuilding* m_Building;
	TArray<AActor*> CorrectedActors;
	bool SpawnedBaseUI = false;
	bool SpawnedBarrackUI = false;

	TSubclassOf<class UBarracksUI> BarracksUIClass;
	UBarracksUI* BarracksUI;
	TSubclassOf<class UBaseUI> BaseUIClasss;
	UBaseUI* BaseUI;
	TSubclassOf<class URadarUI> RadarUIClass;
	URadarUI* RadarUI;
	TSubclassOf<class UBuilderUI> BuilderUIClass;
	UBuilderUI* BuilderUI;
	class ATestHUD* HUD;
	UPROPERTY(Replicated)
	ABuildingIcon* BuildingIcon;


};


