// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "GridNavMeshBoundsVolume.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API AGridNavMeshBoundsVolume : public ANavMeshBoundsVolume
{
	GENERATED_BODY()
	AGridNavMeshBoundsVolume();
	
	UPROPERTY(EditAnywhere)
	AGridNavMeshBoundsVolume* NaviMeshOptions;

	TSubclassOf<AGridNavMeshBoundsVolume> NavMeshToSpawn;

	UPROPERTY(EditAnywhere, Category = "Navmesh|Setup")
	TSubclassOf<AGridNavMeshBoundsVolume> NavMesh;
	virtual void BeginPlay() override;

};
