// Fill out your copyright notice in the Description page of Project Settings.


#include "NavmeshSpawner.h"
#include "GridNavMeshBoundsVolume.h"

// Sets default values
ANavmeshSpawner::ANavmeshSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANavmeshSpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANavmeshSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

