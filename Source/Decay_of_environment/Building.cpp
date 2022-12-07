// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Decay_of_environmentPlayerController.h"

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
		FVector mPos;
		mPos = PlayerController->MousePos;
		SetActorLocation(mPos);
		if (PlayerController->leftMouseDown)
		{
			if(PlayerController->leftMouseDown)
			{
				IsPlaced = true;
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


