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
		
		//ACubeTile.GetActorLocation()
		
		mPos = PlayerController->MousePos;
		
		GridPos.X = AlignToGrid(mPos.X, GridManager->TileHorizontalOffset);
		GridPos.Y = AlignToGrid(mPos.Y, GridManager->TileVerticalOffset);
		GridPos.Z = mPos.Z;
		UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f Z: %f"), GridPos.X, GridPos.Y, GridPos.Z);
		SetActorLocation(GridPos);
		if (PlayerController->leftMouseDown)
		{
			if(PlayerController->leftMouseDown)
			{
				IsPlaced = true;
			}
			
		}
	}
		
}
float ABuilding::AlignToGrid(float value, float size)
{
	return std::floor(value / size) * size;
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


