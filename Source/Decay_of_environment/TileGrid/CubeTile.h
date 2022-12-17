// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <Components/StaticMeshComponent.h>

#include "CubeTile.generated.h"

class UStaticMeshComponent;

UENUM()
enum class ECubeTileType : uint8
{
	INVADLID,
	GRASS,
	WATER,
	MAX UMETA(hidden)
};

UCLASS()
class DECAY_OF_ENVIRONMENT_API ACubeTile : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleInstanceOnly, Category = "Tile")
	FIntPoint TileIndex;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	ECubeTileType TileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent* TileMesh;

public:	
	// Sets default values for this actor's properties
	ACubeTile();


};
