// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface.h"
#include "../Decay_of_environmentPlayerController.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>

UUserInterface::UUserInterface(const FObjectInitializer& ObjectInitializer)
{

}

bool UUserInterface::Initialize()
{
	bool Success = Super::Initialize();

	if(!ensure(BuildingButton != nullptr)) return false;
	BuildingButton->OnClicked.AddDynamic(this, &UUserInterface::SpawnBuilding);

	return true;
}

void UUserInterface::SpawnBuilding()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Building"));
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(World->GetFirstPlayerController());
	UE_LOG(LogTemp, Warning, TEXT("Controllers: %d"), World->GetNumPlayerControllers());
	//for (auto Player : World->GetPlayerControllerIterator())
	//{
	//	if (Player == PlayerController->GetLocalPlayer()->player)
	//	{
	//		PlayerController->Player->
	//		UE_LOG(LogTemp, Warning, TEXT("Same");
	//	}
	//}
	if (!ensure(PlayerController != nullptr)) return;
	FVector Location;
	Location = PlayerController->MousePos;
	UE_LOG(LogTemp, Warning, TEXT("Spawned at X: %d Y: %d"), Location.X, Location.Y);
	FRotator Rotation = {0,0,0};
	World->SpawnActor<AActor>(BuildingToSpawn, Location, Rotation);

	
}
