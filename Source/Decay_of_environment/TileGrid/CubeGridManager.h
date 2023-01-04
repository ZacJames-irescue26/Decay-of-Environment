// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeTile.h"
#include "CubeGridManager.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API ACubeGridManager : public AActor
{
	GENERATED_BODY()
public:

	TArray<TArray<ACubeTile*>> CubeGrid;
	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	float TileHorizontalOffset;
	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	float TileVerticalOffset;
	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	int32 GridWidth;
	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	int32 GridHeight;
	
	FVector GridPos;

	float AlignToGrid(float value, float size);
protected:

	TArray<TArray<int32>> CubeGrid2DArray;
	

	UPROPERTY(EditAnywhere, Category = "CubeGrid|Setup")
	TSubclassOf<ACubeTile> GrassCubeTile;

	UPROPERTY(EditAnywhere, Category = "CubeGrid|Setup")
	TSubclassOf<ACubeTile> WaterCubeTile;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DefaultBuilding;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Base;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DefaultCharacter;
	/*UPROPERTY(EditAnywhere, Category = "Units|Spawn")
	TSubclassOf<ADecay_of_environmentCharacter> basicUnitSpawn;*/
	
public:	
	// Sets default values for this actor's properties
	ACubeGridManager();
	void LoadLevel();
	void LoadUnitsAndBuildings();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};