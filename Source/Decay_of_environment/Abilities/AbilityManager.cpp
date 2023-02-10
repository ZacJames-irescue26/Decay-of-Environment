// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityManager.h"
#include "../Decay_of_environmentCharacter.h"
#include "ShieldAblitity.h"

// Sets default values
AAbilityManager::AAbilityManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbilityManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbilityManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAbilityManager::DashAbility(TArray<ADecay_of_environmentCharacter*> selectedUnits)
{
	for (ADecay_of_environmentCharacter* units : selectedUnits)
	{
		if (units->stats.unitID == 1)
		{
			if (units->stats.Energy >= 5)
			{
				FVector Location = units->GetActorLocation();
				FRotator Rotation = { 0,0,0 };
				ADash* _Dash = GetWorld()->SpawnActor<ADash>(Dash, Location, Rotation);
				_Dash->SetParentActor(units);
				units->stats.Energy -= 5;
				//units->SetActorLocation(FVector(100,100,1));
				break;
			}

		}

	}
}

void AAbilityManager::Shield(TArray<ADecay_of_environmentCharacter*> selectedUnits)
{
	for (ADecay_of_environmentCharacter* units : selectedUnits)
	{
		if (units->stats.unitID == 1)
		{
			if (units->stats.Energy >= 5)
			{
				FVector Location = units->GetActorLocation();
				FRotator Rotation = { 0,0,0 };
				AShieldAblitity* _Shield = GetWorld()->SpawnActor<AShieldAblitity>(AbilityToSpawn, Location, Rotation);
				_Shield->SetParentActor(units);
				units->stats.Energy -= 5;
				break;
			}

		}

	}
}

