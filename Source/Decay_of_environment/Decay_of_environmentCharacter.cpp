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

	stats.currentHealth = 100;
	stats.maxHealth =  100;
	stats.gatherAmount = 5;
	stats.unitName = "Character";
}

void ADecay_of_environmentCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
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
