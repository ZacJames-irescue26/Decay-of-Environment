// Fill out your copyright notice in the Description page of Project Settings.


#include "UnbuiltBuilding.h"
#include <Kismet/GameplayStatics.h>
#include "TileGrid/CubeGridManager.h"
#include "Decay_of_environmentPlayerController.h"
#include "Net/UnrealNetwork.h"
// Sets default values
AUnbuiltBuilding::AUnbuiltBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	buildingStats.currentHealth = 10.0f;
	bReplicates = true;
	
}


void AUnbuiltBuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AUnbuiltBuilding, buildingStats);
}

// Called when the game starts or when spawned
void AUnbuiltBuilding::BeginPlay()
{
	Super::BeginPlay();
	buildingStats.currentHealth = 10.0f;
	PlayerController = Cast<ADecay_of_environmentPlayerController>(GetWorld()->GetFirstPlayerController());

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
		GetWorld()->GetTimerManager().SetTimer(BuildTimerhandle, this, &AUnbuiltBuilding::SpawnBuilding, 1.0f, false,0.0f);
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


void AUnbuiltBuilding::SpawnBuilding()
{
	AActor* BuildingOwner = this->GetOwner();
	CurrentTime++;
	if (buildingStats.currentHealth < buildingStats.maxHealth)
	{
		Server_BuildHealth();
	}
	
	if (BuildingToSpawn && CurrentTime >= BuildTimer)
	{
		PlayerController->SpawnBuiltBuilding(this->GetActorLocation(), this->GetActorRotation(), this);
	}
}

void AUnbuiltBuilding::Server_BuildHealth_Implementation()
{
	buildingStats.currentHealth += buildingStats.maxHealth / BuildTimer;
}

