// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include <Misc/FileHelper.h>
#include <Kismet/GameplayStatics.h>
#include "../TeamInterface.h"

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
	UGameplayStatics::GetAllActorsWithInterface( GetWorld(), UTeamInterface::StaticClass(), AllActors);
	TArray<FString> SaveText;
	for (int i = 0; i < 10; i++)
	{
		SaveText.Add("Test");
	}
	for (AActor* Actor : AllActors)
	{
		SaveText.Add(FString::SanitizeFloat(Actor->GetActorLocation().X));

	}
	for (FString& string : SaveText)
	{
		FinalString += string;
		FinalString += LINE_TERMINATOR;
	}
	FString SavePath = FPaths::ProjectContentDir() + FilePathFromContent + "test.txt";
	FFileHelper::SaveStringToFile(FinalString, *SavePath);
}
