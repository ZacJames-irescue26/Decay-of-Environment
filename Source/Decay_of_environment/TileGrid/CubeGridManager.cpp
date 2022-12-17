// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGridManager.h"

// Sets default values
ACubeGridManager::ACubeGridManager()
{
 	

}

// Called when the game starts or when spawned
void ACubeGridManager::BeginPlay()
{
	Super::BeginPlay();
	CubeGrid2DArray.SetNumZeroed(GridWidth);
	for (int32 i = 0; i < CubeGrid2DArray.Num(); i++)
	{
		CubeGrid2DArray[i].SetNumZeroed(GridHeight);
	}

	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			const float xPos = x * TileHorizontalOffset;
			const float yPos = y * TileVerticalOffset;

			TSubclassOf<ACubeTile> tiletoSpawn = GrassCubeTile;
			if (FMath::RandRange(0.0f, 1.0f) <= ChanceOfWater)
			{
				tiletoSpawn = WaterCubeTile;
			}
			ACubeTile* NewTile = GetWorld()->SpawnActor<ACubeTile>(tiletoSpawn, FVector(FIntPoint(xPos, yPos)),FRotator::ZeroRotator);
			
			NewTile->TileIndex = FIntPoint(x, y);
			NewTile->SetActorLabel(FString::Printf(TEXT("Tile_%d-%d"), x, y));
			CubeGrid2DArray[x][y] = NewTile;
		}
	}
}


