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
	
	CubeGrid2DArray.SetNumZeroed(GridWidth);
	for (int32 i = 0; i < CubeGrid2DArray.Num(); i++)
	{
		CubeGrid2DArray[i].SetNumZeroed(GridHeight);
	}

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
	
	for (int i = 0; i < Parsed.Num(); i++)
	{
		if (i == 0)
		{
			GridWidth = FCString::Atoi(*Parsed[i]);
		}
		if (i == 1)
		{
			GridHeight = FCString::Atoi(*Parsed[i]);
		}
		UE_LOG(LogTemp, Warning, TEXT("File: %s"), *Parsed[i]);
	}
	
	/*for (auto i = 0; i < RetArray.Num(); i++)
	{
		 
		UE_LOG(LogTemp, Warning, TEXT("File: %i"), RetArray[i]);
		if(i = 0)
	}*/
	/*for (int i = 0; i < RetString.Len(); i++)
	{
		if (RetString[i] >= 48 && RetString[i] <= 57)
		{
			UE_LOG(LogTemp, Warning, TEXT("File: %s"), RetString.);
		}
	}*/


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
			//CubeGrid2DArray[x][y] = NewTile;
		}
	}
}


