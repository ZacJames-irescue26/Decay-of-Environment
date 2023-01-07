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
	void Test();
	UFUNCTION(Client, Reliable)
	void MoveUnits(FVector loc);
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

	void AttackTarget(IDamagableInterface* target);
	void RightClick();
	void GatherResources(IResourceInterface* res);

	ITeamInterface* GetTeam(AActor* other);
	IResourceInterface* GetResource(AActor* other);
	AOverseerer* GetOverseerer();
	void ZoomIn();
	void ZoomOut();
	IDamagableInterface* GetDamagable(AActor* other);

	


private:
	
	void SelectUnits();
	

private:
	
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

	TArray<ADecay_of_environmentCharacter*> selectedUnits;
	TSubclassOf<UUserWidget> characterUItemplate;
	UCharacterDetails* characterUI;

	TSubclassOf<class UUserWidget> UserInterfaceClass;
	class UUserInterface* UserInterface;
};


