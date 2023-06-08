// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingIcon.h"
#include "TileGrid/CubeGridManager.h"
#include "Kismet/GameplayStatics.h"
#include "Decay_of_environmentPlayerController.h"
#include "UnbuiltBuilding.h"
// Sets default values
ABuildingIcon::ABuildingIcon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingIcon::BeginPlay()
{
	Super::BeginPlay();
	GridManager = Cast<ACubeGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACubeGridManager::StaticClass()));

}

// Called every frame
void ABuildingIcon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsPlaced)
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(World->GetFirstPlayerController());
		if (!ensure(PlayerController != nullptr)) return;

		//ACubeTile.GetActorLocation().X

		FVector mPos = PlayerController->MousePos;

		GridManager->GridPos.X = GridManager->AlignToGrid(mPos.X, GridManager->TileHorizontalOffset);
		GridManager->GridPos.Y = GridManager->AlignToGrid(mPos.Y, GridManager->TileVerticalOffset);
		GridManager->GridPos.Z = mPos.Z;

		//UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f Z: %f"), GridManager->GridPos.X, GridManager->GridPos.Y, GridManager->GridPos.Z);
		if (GridManager->GridPos.X / GridManager->TileHorizontalOffset >= 0 && GridManager->GridPos.Y / GridManager->TileVerticalOffset >= 0)
		{
			SetActorLocation(GridManager->GridPos);
			if (PlayerController->leftMouseDown)
			{
				if (PlayerController->leftMouseDown)
				{
					IsPlaced = true;
					GridManager->CubeGrid[GridManager->GridPos.X / GridManager->TileHorizontalOffset][GridManager->GridPos.Y / GridManager->TileVerticalOffset]->IsOccupied = true;
					AUnbuiltBuilding* Building = GetWorld()->SpawnActor<AUnbuiltBuilding>(BuildingToSpawn, GetActorLocation(), GetActorRotation());
				}


			}
		}
	}
}

