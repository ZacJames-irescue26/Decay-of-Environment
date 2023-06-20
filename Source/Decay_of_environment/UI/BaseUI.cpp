// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUI.h"
#include "Components/Button.h"
#include "Decay_of_environment/Decay_of_environmentPlayerController.h"
#include "Decay_of_environment/BuildingIcon.h"

bool UBaseUI::Initialize()
{
	bool Success = Super::Initialize();
	if (BuildBaseButton == nullptr) return false;
	BuildBaseButton->OnClicked.AddDynamic(this, &UBaseUI::SpawnBase);

	return true;
}
void UBaseUI::SpawnBase()
{
	ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(GetOwningPlayer());

	if (PlayerController != nullptr)
	{
		PlayerController->SpawnBuilding(BaseToSpawn);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController in nullptr"));
	}
}