// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../TileGrid/CubeTile.h"
#include "../TileGrid/CubeGridManager.h"
#include "A_star_AIController.generated.h"

/**
 * 
 */
//USTRUCT(BlueprintType)
//struct Node
//{
//	GENERATED_USTRUCT_BODY()
//public:
//	
//};

UCLASS()
class DECAY_OF_ENVIRONMENT_API AA_star_AIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	ACubeGridManager* GridManager;
	static bool isValid(int x, int y, int32 MapXSize, int32 MapYSize);
	static bool IsDestination(int x, int y, ACubeTile* TileDest, float TileHorizontalOffset, float TileVerticalOffset);
	static float CalculatehCost(int x, int y, ACubeTile* TileDest);
	static TArray<ACubeTile*> A_star(ACubeTile* start, ACubeTile* end, float TileHorizontalOffset, float TileVerticalOffset, int32 MapXSize, int32 MapYSize, TArray<TArray<ACubeTile*>> AllMap);
	static TArray<ACubeTile*> MakePath(TArray<TArray<ACubeTile*>> map, float TileHorizontalOffset, float TileVerticalOffset, ACubeTile* end);
};