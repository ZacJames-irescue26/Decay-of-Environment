// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface.h"

#include <GameFramework/Actor.h>
#include <GameFramework/Character.h>
#include "Kismet/GameplayStatics.h"
#include "../Overseerer.h"
#include "MissionWidget.h"



UUserInterface::UUserInterface(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MissionBPClass(TEXT("/Game/TopDown/Blueprints/UI/BP_MissionText"));
	if (!ensure(MissionBPClass.Class != nullptr)) return;

	MissionClass = MissionBPClass.Class;
}

bool UUserInterface::Initialize()
{
	bool Success = Super::Initialize();

	World = GetWorld();
	if (!ensure(World != nullptr)) return false;
	PlayerController = Cast<ADecay_of_environmentPlayerController>(World->GetFirstPlayerController());
	if(!ensure(BuildingButton != nullptr)) return false;
	BuildingButton->OnClicked.AddDynamic(this, &UUserInterface::SpawnBuilding);
	if (!ensure(UnitButton != nullptr)) return false;
	UnitButton->OnClicked.AddDynamic(this, &UUserInterface::SpawnUnit);
	if (!ensure(Ability1 != nullptr)) return false;
	Ability1->OnClicked.AddDynamic(this, &UUserInterface::Button1);
	if (!ensure(Ability2 != nullptr)) return false;
	Ability2->OnClicked.AddDynamic(this, &UUserInterface::Button2);

	
	FString Path = FString("/Game/TopDown/Textures/exit_icon");
	UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Path));
	AbilityImage->SetVisibility(ESlateVisibility::Visible);
	AbilityImage->SetBrushFromTexture(Texture);
	return true;
}

void UUserInterface::SpawnBuilding()
{
	PlayerController->SpawnBuilding();
}

void UUserInterface::SwitchAbilities(UWidget* Widget)
{
	AbilitySwitcher->SetActiveWidget(Widget);
}


void UUserInterface::UpdateText()
{
	
	ComponentsValue->SetText(FText::FromString(FString::FromInt(PlayerController->GetOverseerer()->statistics.ComponentsValue)));
	
	UMissionDataAsset* MissionData = PlayerController->GetMissionDataAsset();
	FMission* LevelMission = MissionData->MissionMap.Find("Mission2");
	switch(LevelMission->Objectivetype)
	{
	case EObjectiveType::killUnits:
	{
		FText text = FText::FromString(LevelMission->MissionText);
		mission->MissionText->SetText(text);
		int PlayerProgression =PlayerController->GetOverseerer()->statistics.UnitsKilled;
		FString FractionText = FString::Printf(TEXT("%d/%d"), PlayerProgression, LevelMission->MissionObjective);
		mission->MissionProgress->SetText(FText::FromString(FractionText));
		break;
	}
	case EObjectiveType::CollectResources:
	{
		FText text = FText::FromString(LevelMission->MissionText);
		mission->MissionText->SetText(text);
		int PlayerProgression = PlayerController->GetOverseerer()->statistics.ComponentsValue;
		FString FractionText = FString::Printf(TEXT("%d/%d"), PlayerProgression, LevelMission->MissionObjective);
		mission->MissionProgress->SetText(FText::FromString(FractionText));
		break;
	}
	default:
		break;
	}
}

void UUserInterface::Mission()
{	
	
	mission = CreateWidget<UMissionWidget>(GetWorld(), MissionClass);
	if (!ensure(mission != nullptr)) return;
	
	UpdateText();
	MissionBox->AddChild(mission);
}



void UUserInterface::SpawnUnit()
{
	PlayerController->SpawnUnit();
}

void UUserInterface::Button1()
{
	switch (AbilitySwitcher->GetActiveWidgetIndex())
	{
	case 0:
		break;
	case 1:
		PlayerController->Shield();
		break;
	default:
		break;
	}

}

void UUserInterface::Button2()
{
	switch (AbilitySwitcher->GetActiveWidgetIndex())
	{
	case 0:
		break;
	case 1:
		PlayerController->DashAbility();
		break;
	default:
		break;
	}
	//for (ADecay_of_environmentCharacter* units : PlayerController->GetUnitsArray())
	//{
	//	if (units->stats.unitID == 1)
	//	{
	//		if (units->stats.Energy >= 5)
	//		{
	//			FVector Location = units->GetActorLocation();
	//			FRotator Rotation = { 0,0,0 };
	//			ADash* _Dash = GetWorld()->SpawnActor<ADash>(Dash, Location, Rotation);
	//			_Dash->SetParentActor(units);
	//			units->stats.Energy -= 5;
	//			//units->SetActorLocation(FVector(100,100,1));
	//			break;
	//		}

	//	}

	//}
}

