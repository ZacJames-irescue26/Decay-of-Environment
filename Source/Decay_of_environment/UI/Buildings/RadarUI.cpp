// Fill out your copyright notice in the Description page of Project Settings.


#include "RadarUI.h"
#include "Decay_of_environment/Decay_of_environmentPlayerController.h"
#include "Components/Button.h"

bool URadarUI::Initialize()
{
	bool Success = Super::Initialize();
	if(BuildRadarButton == nullptr) return false;
	BuildRadarButton->OnClicked.AddDynamic(this, &URadarUI::SpawnRadar);

	return true;
}

void URadarUI::SpawnRadar()
{
	ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->SpawnBuilding(RadarToSpawn);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController in nullptr"));
	}
}
