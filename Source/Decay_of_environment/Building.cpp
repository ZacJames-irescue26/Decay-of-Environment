// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Decay_of_environmentPlayerController.h"
#include "TileGrid/CubeTile.h"
#include <Kismet/GameplayStatics.h>
#include "TileGrid/CubeGridManager.h"

ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	buildingStats.maxHealth = 1000;
	buildingStats.currentHealth = buildingStats.maxHealth;
	buildingStats.unitName = "Building";
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
	GridManager = Cast<ACubeGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACubeGridManager::StaticClass()));
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsPlaced)
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(World->GetFirstPlayerController());
		if (!ensure(PlayerController != nullptr)) return;
		
		//ACubeTile.GetActorLocation().X
		
		mPos = PlayerController->MousePos;
		
		GridManager->GridPos.X = GridManager->AlignToGrid(mPos.X, GridManager->TileHorizontalOffset);
		GridManager->GridPos.Y = GridManager->AlignToGrid(mPos.Y, GridManager->TileVerticalOffset);
		GridManager->GridPos.Z = mPos.Z;

		//UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f Z: %f"), GridManager->GridPos.X, GridManager->GridPos.Y, GridManager->GridPos.Z);
		if (GridManager->GridPos.X / GridManager->TileHorizontalOffset >= 0 && GridManager->GridPos.Y/GridManager->TileVerticalOffset >= 0)
		{
			SetActorLocation(GridManager->GridPos);
			if (PlayerController->leftMouseDown)
			{
				if (PlayerController->leftMouseDown)
				{
					IsPlaced = true;
					GridManager->CubeGrid[GridManager->GridPos.X / GridManager->TileHorizontalOffset][GridManager->GridPos.Y / GridManager->TileVerticalOffset]->IsOccupied = true;
				}


			}
		}
	}
	
}

void ABuilding::TakeDamage(float damage)
{
	buildingStats.currentHealth -= damage;
}

float ABuilding::GetHealth()
{
	return buildingStats.currentHealth;
}

float ABuilding::GetMaxHealth()
{
	return buildingStats.maxHealth;
}

int32 ABuilding::GetPlayerTeam()
{
	return buildingStats.team;
}

int32 ABuilding::GetPlayerOwner()
{
	return buildingStats.owner;
}

void ABuilding::SetPlayerTeam(int32 Value)
{
	buildingStats.team = Value;
}

void ABuilding::SetPlayerOwner(int32 Value)
{
	buildingStats.owner = Value;
}


