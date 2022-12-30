// Fill out your copyright notice in the Description page of Project Settings.


#include "A_star_AIController.h"
#include <Kismet/GameplayStatics.h>
#include "../TileGrid/CubeGridManager.h"

void AA_star_AIController::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AA_star_AIController::isValid(int x, int y, int32 MapXSize, int32 MapYSize)
{
	if(x < 0 || y < 0 || x >= MapXSize || y >= MapYSize)
	{
		return false;
	}
	return true;
}

bool AA_star_AIController::IsDestination(int x, int y, ACubeTile* TileDest, float TileHorizontalOffset, float TileVerticalOffset)
{
	if (x == TileDest->GetActorLocation().X/TileHorizontalOffset && y == TileDest->GetActorLocation().Y/TileVerticalOffset)
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

TArray<ACubeTile*> AA_star_AIController::A_star(ACubeTile* start, ACubeTile* end, float TileHorizontalOffset, float TileVerticalOffset, int32 MapXSize, int32 MapYSize, TArray<TArray<ACubeTile*>> AllMap )
{
	TArray<ACubeTile*> empty;
	if (isValid(end->GetActorLocation().X/ TileHorizontalOffset, end->GetActorLocation().Y/TileVerticalOffset, MapXSize, MapYSize) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destination is an obstacle"));
		return empty;
	}
	if (IsDestination(start->GetActorLocation().X, start->GetActorLocation().Y, end, TileHorizontalOffset, TileVerticalOffset))
	{
		UE_LOG(LogTemp, Warning, TEXT("You are the destination"));
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
	
	int x = start->GetActorLocation().X/ TileHorizontalOffset;
	/*UE_LOG(LogTemp, Warning, TEXT("X: %f / %f"), start->GetActorLocation().X, TileHorizontalOffset);*/
	int y = start->GetActorLocation().Y/ TileVerticalOffset;
	/*UE_LOG(LogTemp, Warning, TEXT("Y: %f / %f"), start->GetActorLocation().Y, TileVerticalOffset);*/

	AllMap[x][y]->fCost = 0.0f;
	AllMap[x][y]->gCost = 0.0f;
	AllMap[x][y]->hCost = 0.0f;
	AllMap[x][y]->ParentX = x;
	AllMap[x][y]->ParentY = y;

	TArray<ACubeTile*> OpenList;
	OpenList.Add(AllMap[x][y]);
	bool DestinationFound = false;
	while (!OpenList.IsEmpty() && OpenList.Num() < MapYSize * MapXSize)
	{
		ACubeTile* Tile = nullptr;
		do 
		{
			float temp = FLT_MAX;
			ACubeTile* itTile = nullptr;
			for(int32 i = 0; i < OpenList.Num(); i++)
			{
				if(OpenList[i]->fCost < temp)
				{
					temp = OpenList[i]->fCost;
					itTile = OpenList[i];
				}
			}
			Tile = itTile;
			OpenList.Remove(Tile);
		} while (isValid(Tile->GetActorLocation().X / TileHorizontalOffset, Tile->GetActorLocation().Y / TileVerticalOffset, MapXSize, MapYSize) == false);
		x = Tile->GetActorLocation().X / TileHorizontalOffset;
		y = Tile->GetActorLocation().Y / TileVerticalOffset;
		ClosedList[x][y] = true;
		
		for (int32 newX = -1; newX <= 1; newX++)
		{
			for (int32 newY = -1; newY <= 1; newY++)
			{
				float gNew, hNew, fNew;
				if (isValid(x + newX, y + newY, MapXSize, MapYSize))
				{
					if (IsDestination(x + newX, y + newY, end, TileHorizontalOffset, TileVerticalOffset))
					{
						AllMap[x + newX][y + newY]->ParentX = x;
						AllMap[x + newX][y + newY]->ParentY = y;
						DestinationFound = true;
						return MakePath(AllMap, TileHorizontalOffset, TileVerticalOffset, end);
					}
					else if (ClosedList[x + newX][y + newY] == false)
					{
						gNew = Tile->gCost + 1;
						hNew = CalculatehCost(x + newX, y + newY, end);
						fNew = gNew + hNew;
						if (AllMap[x + newX][y + newY]->fCost == FLT_MAX || AllMap[x + newX][y + newY]->fCost > fNew)
						{
							AllMap[x + newX][y + newY]->fCost = fNew;
							AllMap[x + newX][y + newY]->gCost = gNew;
							AllMap[x + newX][y + newY]->hCost = hNew;
							AllMap[x + newX][y + newY]->ParentX = x;
							AllMap[x + newX][y + newY]->ParentY = y;
							OpenList.Add(AllMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (DestinationFound == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destination not found"));
		return empty;
	}
	return empty;
}

TArray<ACubeTile*> AA_star_AIController::MakePath(TArray<TArray<ACubeTile*>> map, float TileHorizontalOffset, float TileVerticalOffset, ACubeTile* end)
{
	/*auto pred = [](AA_star_AIController const& lhs, AA_star_AIController const& rhs)
	{
		return lhs.GetFValue < rhs.GetFValue();
	};*/
	UE_LOG(LogTemp, Warning, TEXT("Path found"));

	int x = end->GetActorLocation().X / TileHorizontalOffset;
	int y = end->GetActorLocation().Y / TileVerticalOffset;
	TArray<ACubeTile*> path;
	TArray<ACubeTile*> usablePath;
	while (!(map[x][y]->ParentX == x && map[x][y]->ParentY == y) && map[x][y]->GetActorLocation().X / TileHorizontalOffset != -1 && map[x][y]->GetActorLocation().Y / TileVerticalOffset != -1)
	{
		path.Add(map[x][y]);
		int tempX = map[x][y]->ParentX;
		int tempY = map[x][y]->ParentY;
		x = tempX;
		y = tempY;

	}
	path.Add(map[x][y]);
	/*for (int i = path.Num(); i >= 0; i--)
	{
		usablePath.Add(path[i]);
	}*/
	//path.Empty();
	/*while (!path.IsEmpty()) {
		ACubeTile* top;
		path.FindLast(top);
		path.Remove(top);
		usablePath.Add(top);
	}*/
	return path;
}

