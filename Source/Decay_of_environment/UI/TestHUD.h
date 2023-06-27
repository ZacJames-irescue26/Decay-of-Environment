// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserInterface.h"
#include "../Decay_of_environmentCharacter.h"
#include "TestHUD.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API ATestHUD : public AHUD
{
	GENERATED_BODY()
public:

	ATestHUD();
	virtual void DrawHUD() override;
	ADecay_of_environmentPlayerController* PlayerController;
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void PressAbiltiy1();

	TSubclassOf<class UUserWidget> UserInterfaceClass;
	class UUserInterface* UserInterface;
	void StartDraw();
	double StartX;
	double StartY;
	TSubclassOf<ADecay_of_environmentCharacter> ActorClass;
	TArray<AActor*> SelectedActors;

	bool SpawnedBaseUI = false;
	bool SpawnedBarrackUI = false;
	class AOverseerer* overseeer;
};
