// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderUI.h"

#include "Decay_of_environment/Decay_of_environmentPlayerController.h"
#include "Components/Button.h"
#include "Decay_of_environment/Decay_of_environmentCharacter.h"

bool UBuilderUI::Initialize()
{
	bool Success = Super::Initialize();
	if (BuildBuilderButton == nullptr) return false;
	BuildBuilderButton->OnClicked.AddDynamic(this, &UBuilderUI::SpawnBuilder);

	return true;
}

void UBuilderUI::SpawnBuilder()
{
	ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(GetOwningPlayer());


	if (PlayerController != nullptr)
	{
		PlayerController->SpawnUnit(BuilderToSpawn, PlayerController->GetState());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController in nullptr"));
	}
}