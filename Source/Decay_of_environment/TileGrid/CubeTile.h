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

	UPROPERTY(EditAnywhere)
	bool IsOccupied = false;

	UPROPERTY(VisibleAnywhere)
	float gCost = 0;	// distance between Current node and start node
	UPROPERTY(VisibleAnywhere)
	float hCost = 0;	// estimated distance from current node to end node
	UPROPERTY(VisibleAnywhere)
	float fCost = 0;	// total cost of node
	UPROPERTY(VisibleAnywhere)
	float ParentX = 0;
	UPROPERTY(VisibleAnywhere)
	float ParentY = 0;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	ECubeTileType TileType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent* TileMesh;

public:	
	// Sets default values for this actor's properties
	ACubeTile();


};
