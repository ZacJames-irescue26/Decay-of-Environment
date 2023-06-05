// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Decay_of_environment/Decay_of_environmentCharacter.h"
#include <Engine/World.h>
#include "Decay_of_environment/Enums_Structs.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	/*FVector SpawnPos = FVector(1560.000000, -2870.000000, -130.000000);
	TMap<int, EUnitClass> characters;
	characters.Emplace(4,EUnitClass::trooper);
	TArray<FVector> waypoints;
	waypoints.Add({-3200.000000, 2370.000000, -130.000000});
	SpawnWave(SpawnPos, characters, waypoints);*/
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::SpawnWave(FVector Spawnposition, TMap<int, EUnitClass> SpawnCharacters, TArray<FVector> Waypoints)
{
	FRotator Rotation = { 0,0,0 };
	for (auto& Unit : SpawnCharacters)
	{
		for (int i = 0; i < Unit.Key; i++)
		{
			ADecay_of_environmentCharacter* EnemyCharacter;
			TSubclassOf<AActor> ActorToSpawn;
			switch (Unit.Value)
			{
			case EUnitClass::worker:
			
				ActorToSpawn = SpawnWorker;
				EnemyCharacter = GetWorld()->SpawnActor<ADecay_of_environmentCharacter>(ActorToSpawn, Spawnposition, Rotation);
				for (int j = 0; j < Waypoints.Num(); j++)
				{
					EnemyCharacter->Waypoints.Add(Waypoints[j]);
				}
				EnemyCharacters.Add(EnemyCharacter);
				break;

			case EUnitClass::trooper:
				ActorToSpawn = SpawnArmy;
				EnemyCharacter = GetWorld()->SpawnActor<ADecay_of_environmentCharacter>(ActorToSpawn, Spawnposition + FVector(10*i,10*i,Spawnposition.Z), Rotation);
				if (EnemyCharacter)
				{
					for (int j = 0; j < Waypoints.Num(); j++)
					{
						EnemyCharacter->Waypoints.Add(Waypoints[j]);
					}
					EnemyCharacters.Add(EnemyCharacter);

				}
				break;

			default:
				break;
			}
			
			
		}
	}
}

