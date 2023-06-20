// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeGridManager.h"
#include <HAL/PlatformFileManager.h>
#include <stdlib.h>
#include <Containers/UnrealString.h>
#include "../Building.h"
#include "../Decay_of_environmentCharacter.h"


// Sets default values
ACubeGridManager::ACubeGridManager()
{
 	
	
}

// Called when the game starts or when spawned
void ACubeGridManager::BeginPlay()
{
	Super::BeginPlay();


	LoadLevel();
	LoadUnitsAndBuildings();


}

float ACubeGridManager::AlignToGrid(float value, float size)
{
	return std::floor(value / size) * size;
}

FVector2D ACubeGridManager::WorldToGridIndex(FVector2D Pos)
{
	int xPos = FMath::RoundToInt((Pos.X / 200)/2);
	int yPos = FMath::RoundToInt((Pos.Y/200)/2);
	//Hack for some reason wont divide by 200
	return FVector2D(xPos, yPos);
}
bool ACubeGridManager::CheckGridIndex(FVector2D Pos)
{
	if (Pos.X >= 0 && Pos.X < CubeGrid.Num() && Pos.Y >= 0 && Pos.Y < CubeGrid[0].Num())
	{
		return true;
	}
	return false;
}

bool ACubeGridManager::IsOccupied(FVector2D Pos)
{
	if (!CheckGridIndex(Pos))
	{
		UE_LOG(LogTemp, Warning, TEXT("grid index is outside the grid"));
		return true;
	}
	
	if (CubeGrid[Pos.X][Pos.Y]->IsOccupied)
	{
		return true;
	}
	return false;
}

void ACubeGridManager::LoadLevel()
{
	FString FilePathFromContent = "TopDown/Maps/Map_txt_files/";
	UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *(FPaths::EngineContentDir() + FilePathFromContent + "MapTest.txt"));


	FString FilePath = FPaths::ProjectContentDir() + FilePathFromContent + "MapTest.txt";
	FString RetString;
	TArray<uint8> RetArray;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("File doesnt exist"));
		return;
	}
	if (!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read file"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("File: %s"), *RetString);
	TArray<FString> Parsed;
	const TCHAR* Delims[] = { TEXT(","), TEXT("\n"), TEXT("\r") };



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
			if (CubeGrid2DArray[x][y] == 0)
			{
				tiletoSpawn = GrassCubeTile;
			}
			if (CubeGrid2DArray[x][y] == 1)
			{
				tiletoSpawn = WaterCubeTile;
			}
			if (CubeGrid2DArray[x][y] == 3)
			{
				tiletoSpawn = RampLeft;
			}
			ACubeTile* NewTile = GetWorld()->SpawnActor<ACubeTile>(tiletoSpawn, FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator);
			//NewTile->SetActorLabel(FString::Printf(TEXT("Tile %d-%d"), x, y));
			CubeGrid[x][y] = NewTile;
		}
	}
}

void ACubeGridManager::LoadUnitsAndBuildings()
{
	FString FilePathFromContent = "TopDown/Maps/Map_txt_files/";
	UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *(FPaths::EngineContentDir() + FilePathFromContent + "MapTest.txt"));
	FString RetString;

	FString FilePath = FPaths::ProjectContentDir() + FilePathFromContent + "test.txt";
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("File doesnt exist"));
		return;
	}
	if (!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to read file"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Ret string length: %i"), RetString.Len());

	const TCHAR* Delims[] = { TEXT(","), TEXT("\n"), TEXT("\r") };
	TArray<FString> Parsed;
	RetString.ParseIntoArray(Parsed, Delims, true);
	UE_LOG(LogTemp, Warning, TEXT("Parsed length: %i"), Parsed.Num());
	for (int i = 0; i < Parsed.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Parsed atoi %i"), FCString::Atoi(*Parsed[i]));
		UE_LOG(LogTemp, Warning, TEXT("Parsed atof %f"), FCString::Atof(*Parsed[i]));
	}

	//for (int i = 0; i < Parsed.Num(); i+= 4)
	int i = 0;
	while(i < (Parsed.Num()-4))
	{
		if (i > Parsed.Num())
		{
			break;
		}
		TSubclassOf<AActor> ActorToSpawn;
		int unitID = FCString::Atoi(*Parsed[i]);
		FVector Pos = { FCString::Atof(*Parsed[i+1]),FCString::Atof(*Parsed[i+2]), FCString::Atof(*Parsed[i+3])};
		ABuilding* NewBuilding;
		ABuilding* NewBase;
		ADecay_of_environmentCharacter* NewCharacter;
		switch (unitID)
		{
		case 0:
			ActorToSpawn = DefaultBuilding;
			NewBuilding = GetWorld()->SpawnActor<ABuilding>(ActorToSpawn, Pos, FRotator::ZeroRotator);
			
			break;
		case 1:
			ActorToSpawn = Base;
			NewBase = GetWorld()->SpawnActor<ABuilding>(ActorToSpawn, Pos, FRotator::ZeroRotator);
			
			break;
		case 10:
			ActorToSpawn = DefaultCharacter;
			NewCharacter = GetWorld()->SpawnActor<ADecay_of_environmentCharacter>(ActorToSpawn, Pos, FRotator::ZeroRotator);
			
			break;
		default:
			break;
		}
		UE_LOG(LogTemp, Warning, TEXT("value: %i"), i);
		i += 4;
		UE_LOG(LogTemp, Warning, TEXT("value: %i"), i);
	}
	



}

