// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridNavMeshBoundsVolume.h"
#include "NavmeshSpawner.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API ANavmeshSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavmeshSpawner();
	TSubclassOf<AGridNavMeshBoundsVolume> NavMeshToSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
