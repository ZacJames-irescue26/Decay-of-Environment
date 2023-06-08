// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingIcon.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API ABuildingIcon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingIcon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	bool IsPlaced = false;
	class ACubeGridManager* GridManager;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUnbuiltBuilding> BuildingToSpawn;
};
