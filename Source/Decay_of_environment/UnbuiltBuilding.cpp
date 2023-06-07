// Fill out your copyright notice in the Description page of Project Settings.


#include "UnbuiltBuilding.h"
#include <Kismet/GameplayStatics.h>
#include "TileGrid/CubeGridManager.h"
#include "Decay_of_environmentPlayerController.h"
// Sets default values
AUnbuiltBuilding::AUnbuiltBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	buildingStats.currentHealth = 10.0f;
}

// Called when the game starts or when spawned
void AUnbuiltBuilding::BeginPlay()
{
	Super::BeginPlay();
	buildingStats.currentHealth = 10.0f;
	GridManager = Cast<ACubeGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACubeGridManager::StaticClass()));

}

// Called every frame
void AUnbuiltBuilding::Tick(float DeltaTime)
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
		if (GridManager->GridPos.X / GridManager->TileHorizontalOffset >= 0 && GridManager->GridPos.Y / GridManager->TileVerticalOffset >= 0)
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

void AUnbuiltBuilding::StartTimer()
{
	isPaused = false;
	if (!GetWorld()->GetTimerManager().IsTimerActive(BuildTimerhandle))
	{
		GetWorld()->GetTimerManager().SetTimer(BuildTimerhandle, this, &AUnbuiltBuilding::SpawnBuidling, 1.0f, false,0.0f);
	}
	else if (GetWorld()->GetTimerManager().IsTimerPaused(BuildTimerhandle))
	{
		GetWorld()->GetTimerManager().UnPauseTimer(BuildTimerhandle);
	}
}

void AUnbuiltBuilding::PauseTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(BuildTimerhandle);
	isPaused = true;
}

void AUnbuiltBuilding::SpawnBuidling()
{
	CurrentTime++;
	if (buildingStats.currentHealth < buildingStats.maxHealth)
	{
		buildingStats.currentHealth += buildingStats.maxHealth / BuildTimer;
	}
	
	if (BuildingToSpawn && CurrentTime >= BuildTimer)
	{
		ABuilding* _Building = GetWorld()->SpawnActor<ABuilding>(BuildingToSpawn,this->GetActorLocation(),this->GetActorRotation());
		this->Destroy();
	}
}

