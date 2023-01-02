// Fill out your copyright notice in the Description page of Project Settings.


#include "GridNavMeshBoundsVolume.h"
#include <UObject/Object.h>
#include <Engine/World.h>

AGridNavMeshBoundsVolume::AGridNavMeshBoundsVolume()
{
	
}
void AGridNavMeshBoundsVolume::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Name = TEXT("NavMesh");
	// Spawninfo has additional info you might want to modify such as the name of the spawned actor.
	//NaviMeshOptions = GetWorld()->SpawnActor<AGridNavMeshBoundsVolume>(NavMeshToSpawn, FVector(0.0f,0.0f,0.0f), FRotator::ZeroRotator);
	/*NaviMeshOptions->Brush->Bounds.BoxExtent.X = 100;
	NaviMeshOptions->Brush->Bounds.BoxExtent.Y = 10;*/
	/*NavMeshToSpawn = NavMesh;
	AGridNavMeshBoundsVolume* NaviSpawn = GetWorld()->SpawnActor<AGridNavMeshBoundsVolume>(NavMeshToSpawn, FVector(0.0f,0.0f,0.0f), FRotator::ZeroRotator);*/
}

