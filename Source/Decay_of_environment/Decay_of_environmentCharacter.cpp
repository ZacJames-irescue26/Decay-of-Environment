// Copyright Epic Games, Inc. All Rights Reserved.

#include "Decay_of_environmentCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "BaseAI.h"
#include "Enums_Structs.h"
#include "ResourceInterface.h"
#include <Engine/StaticMesh.h>
#include "Overseerer.h"
#include "Net/UnrealNetwork.h"
//TODO REMOVE
#include "Decay_of_environmentPlayerController.h"
#include "MissionDataAsset.h"
#include "GameFramework/PlayerState.h"

ADecay_of_environmentCharacter::ADecay_of_environmentCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AIControllerClass = ABaseAI::StaticClass();
	stats.AttackRange = 4;
	stats.currentHealth = 100;
	stats.maxHealth =  100;
	stats.gatherAmount = 5;
	stats.unitName = "Character";
	stats.Energy = 10;

	bReplicates = true;
	
}




void ADecay_of_environmentCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADecay_of_environmentCharacter, stats);
}

void ADecay_of_environmentCharacter::DestroyCharacter_Implementation()
{
	this->Destroy(true);
}
void ADecay_of_environmentCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	CollisionSphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));
	CollisionSphere->SetSphereRadius(stats.AttackRange);
	if (m_PlayerController == nullptr)
	{
		m_PlayerController = m_PlayerController == nullptr ? Cast<ADecay_of_environmentPlayerController>(GetWorld()->GetFirstPlayerController()) : m_PlayerController;

	}
	if (stats.currentHealth <= 0 && m_PlayerController)
	{
		if (m_PlayerController->GetUnitsArray().Contains(this))
		{
			m_PlayerController->GetUnitsArray().Remove(this);
			UE_LOG(LogTemp, Warning, TEXT("Removed unit"));

		}
		if (stats.owner < 0)
		{

			m_PlayerController->GetOverseerer()->statistics.UnitsKilled += 1;
		}
		DestroyCharacter();
		DestroyUnit();
	}
}


void ADecay_of_environmentCharacter::BeginPlay()
{
	Super::BeginPlay();
	//TODO REMOVE AND PLACE IN A CHaRAcTER CONTROLLER
	
	SetupMissionWaypoints();
	/*FString sPath = TEXT("/Game/TopDown/Blueprints/Fog_of_war/M_FogOfWar");
	UMaterial* mat = LoadMaterialFromPath(FName(*sPath));*/
	
	Decal = Cast<UDecalComponent>(GetComponentByClass(UDecalComponent::StaticClass()));
	
}

void ADecay_of_environmentCharacter::SetupMissionWaypoints()
{
	FString WorldName = GetWorld()->GetMapName();
	WorldName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *WorldName);
	UE_LOG(LogTemp, Warning, TEXT("%i"), WorldName.Equals(TEXT("Mission1"), ESearchCase::IgnoreCase))
	//TODO Make into objects so more easily placed
		if (WorldName.Equals(TEXT("Mission1"), ESearchCase::IgnoreCase))
		{
			if (stats.MissionWaypoint == 1)
			{
				Waypoints.Add(FVector(380.0, -150.0, 110.0));
				Waypoints.Add(FVector(400.0, -130.0, 110.0));
				Waypoints.Add(FVector(3000.0, -110.0, 110.0));

			}

			if (stats.MissionWaypoint == 2)
			{
				Waypoints.Add(FVector(-2800.0, -710.0, 110.0));
				Waypoints.Add(FVector(400.0, -130.0, 110.0));
				Waypoints.Add(FVector(-2800.0, -1200.0, 110.0));
			}
		}
}

int32 ADecay_of_environmentCharacter::GetWeight()
{
	int32 weight = 0;
	for (FItem item : stats.inventory.items)
	{
		weight += item.amount;
	}
	return weight;
}

int32 ADecay_of_environmentCharacter::GetCarryWeight()
{
	return stats.inventory.capacity;
}

void ADecay_of_environmentCharacter::ClearInventory()
{
	GetStats().inventory.items.Empty();
	//inventoryChange.Broadcast(stats.inventory);
}

int32 ADecay_of_environmentCharacter::GetGatherAmount()
{
	return stats.gatherAmount;
}

void ADecay_of_environmentCharacter::RecieveResources(int32 amount, IResourceInterface* ri)
{
	FItem* itemFound = stats.inventory.FindItem(ri->GetEnumName());

	if (itemFound == NULL)
	{
		FItem item;
		item.amount = amount;
		item.itemName = ri->GetEnumName();
		stats.inventory.items.Add(item);
	}
	else
	{
		itemFound->amount += amount;
	}
}

void ADecay_of_environmentCharacter::TakeDamage(float damage)
{
	stats.currentHealth -= damage;
	ServerTakeDamage(damage);
}


void ADecay_of_environmentCharacter::ServerTakeDamage_Implementation(float damage)
{
	stats.currentHealth -= damage;
}

float ADecay_of_environmentCharacter::GetHealth()
{
	return stats.currentHealth;
}

float ADecay_of_environmentCharacter::GetMaxHealth()
{
	return stats.maxHealth;
}

FCharacterStats& ADecay_of_environmentCharacter::GetStats()
{
	return stats;
}

int32 ADecay_of_environmentCharacter::GetPlayerTeam()
{
	return stats.team;
}

int32 ADecay_of_environmentCharacter::GetPlayerOwner()
{
	return stats.owner;
}

void ADecay_of_environmentCharacter::SetPlayerTeam(int32 Value)
{
	stats.team = Value;
}

void ADecay_of_environmentCharacter::SetPlayerOwner(int32 Value)
{
	stats.owner = Value;
	
}

void ADecay_of_environmentCharacter::DestroyUnit()
{
	Destroy(true);

}






