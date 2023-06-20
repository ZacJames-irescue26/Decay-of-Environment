// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Decay_of_environmentPlayerController.h"
#include "TileGrid/CubeTile.h"
#include "Net/UnrealNetwork.h"

void ABuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABuilding, buildingStats);
}

ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	buildingStats.maxHealth = 1000;
	buildingStats.currentHealth = buildingStats.maxHealth;
	buildingStats.unitName = "Building";
	bReplicates = true;
	
}


void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	Decal = Cast<UDecalComponent>(GetComponentByClass(UDecalComponent::StaticClass()));
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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


void ABuilding::Server_TakeDamage_Implementation(float damage)
{
	buildingStats.currentHealth -= damage;
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


