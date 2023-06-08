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

}

// Called every frame
void AUnbuiltBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

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

