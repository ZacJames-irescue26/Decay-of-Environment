// Fill out your copyright notice in the Description page of Project Settings.


#include "BarracksUI.h"
#include "Decay_of_environment/Decay_of_environmentPlayerController.h"
#include "Components/Button.h"

bool UBarracksUI::Initialize()
{
	bool Success = Super::Initialize();
	if (BuildBarracksButton == nullptr) return false;
	BuildBarracksButton->OnClicked.AddDynamic(this, &UBarracksUI::SpawnBarracks);

	return true;
}

void UBarracksUI::SpawnBarracks()
{
	ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(GetOwningPlayer());

	if (PlayerController != nullptr)
	{
		PlayerController->SpawnBuilding(BarracksToSpawn);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController in nullptr"));
	}
}
