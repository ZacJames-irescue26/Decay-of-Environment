// Fill out your copyright notice in the Description page of Project Settings.


#include "A_star_AIController.h"
#include <Kismet/GameplayStatics.h>
#include "../TileGrid/CubeGridManager.h"

void AA_star_AIController::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AA_star_AIController::isValid(int x, int y)
{
	if(x < 0 || y < 0)
	{
		return false;
	}
	return true;
}

bool AA_star_AIController::IsDestination(int x, int y, ACubeTile* TileDest)
{
	if (x == TileDest->GetActorLocation().X || y == TileDest->GetActorLocation().Y)
	{
		return true;

	}
	return false;
}

float AA_star_AIController::CalculatehCost(int x, int y, ACubeTile* TileDest)
{
	float XDif = x - TileDest->GetActorLocation().X;
	float YDif = y - TileDest->GetActorLocation().Y;
	float hCost = FMath::Sqrt((XDif *XDif) + (YDif * YDif));
	return hCost;
}

TArray<ACubeTile*> AA_star_AIController::A_star(ACubeTile* start, ACubeTile* end,int32 MapXSize, int32 MapYSize, TArray<TArray<ACubeTile*>> AllMap )
{
	TArray<ACubeTile*> empty;
	if (isValid(end->GetActorLocation().X, end->GetActorLocation().Y) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destination is an obstacle"));
		return empty;
	}
	TArray<TArray<bool>> ClosedList;
	ClosedList.SetNumZeroed(MapXSize);
	for (int32 i = 0; i < ClosedList.Num(); i++)
	{
		ClosedList[i].SetNumZeroed(MapYSize);
	}
	for (int x = 0; x < MapXSize; x++)
	{
		for (int y = 0; y < MapYSize; y++)
		{
			AllMap[x][y]->fCost = FLT_MAX;
			AllMap[x][y]->gCost = FLT_MAX;
			AllMap[x][y]->hCost = FLT_MAX;
			AllMap[x][y]->ParentX = -1;
			AllMap[x][y]->ParentY = -1;

			ClosedList[x][y] = false;
		}
	}
	
	int x = start->GetActorLocation().X/MapXSize;
	int y = start->GetActorLocation().Y/MapYSize;

	AllMap[x][y]->fCost = 0.0f;
	AllMap[x][y]->gCost = 0.0f;
	AllMap[x][y]->hCost = 0.0f;
	AllMap[x][y]->ParentX = x;
	AllMap[x][y]->ParentY = y;

	TArray<ACubeTile*> OpenList;
	OpenList.Add(AllMap[x][y]);

	/*while (!OpenList.empty() && OpenList.size() < MapXSize * MapYSize)
	{
		ACubeTile Tile;
		do
		{
			float temp = FLT_MAX;
			TArray<ACubeTile*>::CreateIterator() itTile;
			for (TArray<ACubeTile*>::CreateIterator() it = OpenList.begin(); it != OpenList.end(); it = next(it))
			{
				ACubeTile T = *it;
				if (t.fCost < temp)
				{
					temp = t.fCost;
					itTile = it;
				}
			}
			Tile = *itTile;
			OpenList.erase(itTile);
		}while (isValid(Tile.GetActorLocation().X / MapXSize, Tile.GetActorLocation().Y / MapYSize) == false);
		x = Tile.GetActorLocation().X / MapXSize;
		y = Tile.GetActorLocation().Y / MapYSize;
		ClosedList[x][y] == true;

	}*/
	 return empty;
	
}

