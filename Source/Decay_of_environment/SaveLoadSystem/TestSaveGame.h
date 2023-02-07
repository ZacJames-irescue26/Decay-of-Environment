// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include <AIController.h>
#include "../Enums_Structs.h"
#include "../RTSGameInstance.h"
#include "TestSaveGame.generated.h"




UCLASS()
class DECAY_OF_ENVIRONMENT_API UTestSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(SaveGame, EditAnywhere)
	TArray<FCharacterSaveData> SaveCharacter;
	UPROPERTY(SaveGame, EditAnywhere)
	TArray<FBuildingSaveData> SaveBuildings;
	//void Save(TArray<AActor*> AllCharacters, TArray<AActor*> AllBuildings);
	UPROPERTY(EditAnywhere)
	int32 Test;
	UPROPERTY(EditAnywhere)
	int32 TestSave;
	//void Load();

};
