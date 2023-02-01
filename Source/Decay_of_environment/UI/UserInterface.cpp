// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface.h"

#include <GameFramework/Actor.h>
#include <GameFramework/Character.h>
#include "Kismet/GameplayStatics.h"
#include "../Overseerer.h"
#include "../Abilities/ShieldAblitity.h"
#include "../Abilities/Dash.h"


UUserInterface::UUserInterface(const FObjectInitializer& ObjectInitializer)
{

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
	if (!ensure(ArmyShield != nullptr)) return false;
	ArmyShield->OnClicked.AddDynamic(this, &UUserInterface::SpawnArmyShield);
	if (!ensure(ArmyDash != nullptr)) return false;
	ArmyDash->OnClicked.AddDynamic(this, &UUserInterface::SpawnArmyDash);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ABuilding::StaticClass(), ActorBuildings);
	for (auto& Building : ActorBuildings)
	{
		Buildings.Add(Cast<ABuilding>(Building));
	}
	FString Path = FString("/Game/TopDown/Textures/exit_icon");
	UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Path));

	AbilityImage->SetVisibility(ESlateVisibility::Visible);
	AbilityImage->SetBrushFromTexture(Texture);
	
	return true;
}
void UUserInterface::SwitchAbilities(UWidget* Widget)
{
	AbilitySwitcher->SetActiveWidget(Widget);
}
void UUserInterface::UpdateText()
{
	
	ComponentsValue->SetText(FText::FromString(FString::FromInt(PlayerController->GetOverseerer()->ComponentsValue)));
	
}

void UUserInterface::SpawnBuilding()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Building"));
	
	UE_LOG(LogTemp, Warning, TEXT("Controllers: %d"), World->GetNumPlayerControllers());
	//for (auto Player : World->GetPlayerControllerIterator())
	//{
	//	if (Player == PlayerController->GetLocalPlayer()->player)
	//	{
	//		PlayerController->Player->
	//		UE_LOG(LogTemp, Warning, TEXT("Same");
	//	}
	//}
	if (!ensure(PlayerController != nullptr)) return;
	if (PlayerController->GetOverseerer()->ComponentsValue >= 10)
	{
		FVector Location;
		Location = PlayerController->MousePos;
		//UE_LOG(LogTemp, Warning, TEXT("Spawned at X: %d Y: %d"), Location.X, Location.Y);
		FRotator Rotation = {0,0,0};
		ABuilding* Building = World->SpawnActor<ABuilding>(BuildingToSpawn, Location, Rotation);
		Buildings.Add(Building);
		PlayerController->GetOverseerer()->ComponentsValue -= 10;
	}
	
}

void UUserInterface::SpawnUnit()
{
	for (auto& Building : Buildings)
	{
		if (Building->IsMainBuilding)
		{
			if (PlayerController->GetOverseerer()->ComponentsValue >= 10)
			{
				FVector Location = Building->GetActorLocation();
				Location.X = Location.X + 20;
				UE_LOG(LogTemp, Warning, TEXT("Spawned at X: %d Y: %d"), Location.X, Location.Y);
				FRotator Rotation = {0,0,0};
				World->SpawnActor<AActor>(UnitToSpawn, Location, Rotation);
				PlayerController->GetOverseerer()->ComponentsValue -= 10;
				break;

			}
		}
	}
}

void UUserInterface::SpawnArmyShield()
{
	for (ADecay_of_environmentCharacter* units : PlayerController->GetUnitsArray())
	{
		if (units->stats.unitID == 1)
		{
			if (units->stats.Energy >= 5)
			{
				FVector Location = units->GetActorLocation();
				FRotator Rotation = { 0,0,0 };
				AShieldAblitity* Shield = GetWorld()->SpawnActor<AShieldAblitity>(AbilityToSpawn, Location, Rotation);
				Shield->SetParentActor(units);
				units->stats.Energy -= 5;
				break;
			}

		}

	}
}

void UUserInterface::SpawnArmyDash()
{
	for (ADecay_of_environmentCharacter* units : PlayerController->GetUnitsArray())
	{
		if (units->stats.unitID == 1)
		{
			if (units->stats.Energy >= 5)
			{
				FVector Location = units->GetActorLocation();
				FRotator Rotation = { 0,0,0 };
				ADash* _Dash = GetWorld()->SpawnActor<ADash>(Dash, Location, Rotation);
				_Dash->SetParentActor(units);
				units->stats.Energy -= 5;
				//units->SetActorLocation(FVector(100,100,1));
				break;
			}

		}

	}
}
