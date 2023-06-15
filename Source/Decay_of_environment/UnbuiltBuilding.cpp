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
	DOREPLIFETIME(AUnbuiltBuilding, _Building);
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


void AUnbuiltBuilding::Server_SpawnBuilding_Implementation()
{
	AActor* BuildingOwner = this->GetOwner();
	_Building = GetWorld()->SpawnActor<ABuilding>(BuildingToSpawn, this->GetActorLocation(), this->GetActorRotation());
	_Building->SetOwner(BuildingOwner);
	Multicast_SpawnBuilding();
	this->Destroy(true);
}


void AUnbuiltBuilding::Multicast_SpawnBuilding_Implementation()
{
	AActor* BuildingOwner = this->GetOwner();
	_Building = GetWorld()->SpawnActor<ABuilding>(BuildingToSpawn, this->GetActorLocation(), this->GetActorRotation());
	_Building->SetOwner(BuildingOwner);
}

void AUnbuiltBuilding::SpawnBuilding()
{
	AActor* BuildingOwner = this->GetOwner();
	CurrentTime++;
	if (buildingStats.currentHealth < buildingStats.maxHealth)
	{
		buildingStats.currentHealth += buildingStats.maxHealth / BuildTimer;
	}
	
	if (BuildingToSpawn && CurrentTime >= BuildTimer)
	{
		
		_Building = GetWorld()->SpawnActor<ABuilding>(BuildingToSpawn,this->GetActorLocation(),this->GetActorRotation());
		_Building->SetOwner(BuildingOwner);
		Server_SpawnBuilding();
		this->Destroy();
	}
}

