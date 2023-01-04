// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include <Misc/FileHelper.h>
#include <Kismet/GameplayStatics.h>
#include "../TeamInterface.h"
#include "../Decay_of_environmentCharacter.h"
#include "../Building.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}
	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);

	if (!ensure(SaveButton != nullptr)) return false;
	SaveButton->OnClicked.AddDynamic(this, &UInGameMenu::SaveLevel);
	return true;
}


void UInGameMenu::CancelPressed()
{
	Teardown();
}

void UInGameMenu::QuitPressed()
{
	if (MenuInterface != nullptr)
	{
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}

void UInGameMenu::SaveLevel()
{
	FString FilePathFromContent = "TopDown/Maps/Map_txt_files/";
	FString FinalString = "";
	TArray<AActor*> AllActors;
	TArray<AActor*> AllCharacters;
	TArray<AActor*> AllBuildings;
	//UGameplayStatics::GetAllActorsWithInterface( GetWorld(), UTeamInterface::StaticClass(), AllActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADecay_of_environmentCharacter::StaticClass(), AllCharacters);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuilding::StaticClass(), AllBuildings);
	TArray<FSaveData> SaveText;

	for (AActor* Actor : AllCharacters)
	{
		ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(Actor);
		FSaveData data;
		data.Name = Character->GetName();
		data.X = FString::SanitizeFloat(Character->GetActorLocation().X);
		data.Y = FString::SanitizeFloat(Character->GetActorLocation().Y);
		data.Z = FString::SanitizeFloat(Character->GetActorLocation().Z);
		data.team = FString::FromInt(Character->GetPlayerTeam());
		data.Owner = FString::FromInt(Character->GetPlayerOwner());
		
		data.UnitTypeId = TEXT("10");
		SaveText.Add(data);
		
		/*UGameplayStatics::GetPlayerController()
		UGameplayStatics::SaveGameToSlot()*/

	}
	for (AActor* Actor : AllBuildings)
	{
		ABuilding* Building = Cast<ABuilding>(Actor);
		FSaveData data;
		data.Name = Building->GetName();
		data.X = FString::SanitizeFloat(Building->GetActorLocation().X);
		data.Y = FString::SanitizeFloat(Building->GetActorLocation().Y);
		data.Z = FString::SanitizeFloat(Building->GetActorLocation().Z);
		data.team = FString::FromInt(Building->GetPlayerTeam());
		data.Owner = FString::FromInt(Building->GetPlayerOwner());
		data.UnitTypeId = FString::FromInt(Building->buildingStats.BuildingTypeId);
		SaveText.Add(data);

	}
	for (FSaveData& string : SaveText)
	{
		FinalString += string.UnitTypeId;
		FinalString += TEXT(",");
		FinalString += string.X;
		FinalString += TEXT(",");
		FinalString += string.Y;
		FinalString += TEXT(",");
		FinalString += string.Z;
		//FinalString += string->team;
		FinalString += LINE_TERMINATOR;
	}
	FString SavePath = FPaths::ProjectContentDir() + FilePathFromContent + "test.txt";
	FFileHelper::SaveStringToFile(FinalString, *SavePath);
}
