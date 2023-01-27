// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface.h"

#include <GameFramework/Actor.h>
#include <GameFramework/Character.h>
#include "Kismet/GameplayStatics.h"
#include "../Overseerer.h"


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
