// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserInterface.h"
#include "TestHUD.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API ATestHUD : public AHUD
{
	GENERATED_BODY()
	ATestHUD();

	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	TSubclassOf<class UUserWidget> UserInterfaceClass;
	class UUserInterface* UserInterface;
};
