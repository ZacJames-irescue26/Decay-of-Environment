// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface.h"

UUserInterface::UUserInterface(const FObjectInitializer& ObjectInitializer)
{

}

bool UUserInterface::Initialize()
{
	bool Success = Super::Initialize();

	if(!ensure(BuildingButton != nullptr)) return false;
	BuildingButton->OnClicked.AddDynamic(this, &)
}
