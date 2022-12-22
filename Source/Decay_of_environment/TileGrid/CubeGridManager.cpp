// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGridManager.h"
#include <HAL/PlatformFileManager.h>
#include <stdlib.h>
#include <Containers/UnrealString.h>


// Sets default values
ACubeGridManager::ACubeGridManager()
{
 	
	
}

// Called when the game starts or when spawned
void ACubeGridManager::BeginPlay()
{
	Super::BeginPlay();
	FString FilePathFromContent = "TopDown/Maps/Map_txt_files/";
	UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *(FPaths::EngineContentDir() + FilePathFromContent + "MapTest.txt"));
	

	FString FilePath = FPaths::ProjectContentDir() + FilePathFromContent + "MapTest.txt";
	FString RetString;
	TArray<uint8> RetArray;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("File doesnt exist"));
	}
	if (!FFileHelper::LoadFileToString(RetString, *FilePath ))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read file"));
	}

	UE_LOG(LogTemp, Warning, TEXT("File: %s"), *RetString);
	TArray<FString> Parsed;
	const TCHAR *Delims[]={TEXT(","), TEXT("\n"), TEXT("\r")};
	

	
	RetString.ParseIntoArray(Parsed, Delims, true);

	GridWidth = FCString::Atoi(*Parsed[0]);
	GridHeight = FCString::Atoi(*Parsed[1]);

	CubeGrid2DArray.SetNumZeroed(GridWidth);
	for (int32 i = 0; i < CubeGrid2DArray.Num(); i++)
	{
		CubeGrid2DArray[i].SetNumZeroed(GridHeight);
	}

	CubeGrid.SetNumZeroed(GridWidth);
	for (int32 i = 0; i < CubeGrid.Num(); i++)
	{
		CubeGrid[i].SetNumZeroed(GridHeight);
	}
	int32 temp = 2;

	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			if (temp < Parsed.Num())
			{
				CubeGrid2DArray[x][y] = FCString::Atoi(*Parsed[temp]);
				temp++;
			}
			
		}
	}


	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			const float xPos = x * TileHorizontalOffset;
			const float yPos = y * TileVerticalOffset;
			TSubclassOf<ACubeTile> tiletoSpawn;
			if(CubeGrid2DArray[x][y] == 0)
			{
				tiletoSpawn = GrassCubeTile;
			}
			if (CubeGrid2DArray[x][y] == 1)
			{
				tiletoSpawn = WaterCubeTile;
			}
			ACubeTile* NewTile = GetWorld()->SpawnActor<ACubeTile>(tiletoSpawn, FVector(FIntPoint(xPos, yPos)),FRotator::ZeroRotator);
			NewTile->SetActorLabel(FString::Printf(TEXT("Tile %d-%d"), x, y));
			CubeGrid[x][y] = NewTile;
		}
	}
}


