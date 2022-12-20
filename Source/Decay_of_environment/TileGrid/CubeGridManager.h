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
protected:

	TArray<TArray<int32>> CubeGrid2DArray;
	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	int32 GridWidth;
	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	int32 GridHeight;
	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	float TileHorizontalOffset;
	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	float TileVerticalOffset;

	UPROPERTY(EditAnywhere, Category = "CubeGrid|Setup")
	TSubclassOf<ACubeTile> GrassCubeTile;

	UPROPERTY(EditAnywhere, Category = "CubeGrid|Setup")
	TSubclassOf<ACubeTile> WaterCubeTile;

	UPROPERTY(EditAnywhere, Category = "CubeGrid|Layout")
	float ChanceOfWater;
public:	
	// Sets default values for this actor's properties
	ACubeGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};