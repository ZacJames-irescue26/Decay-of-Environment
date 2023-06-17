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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

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

	FVector Corner1;
	FVector Corner2;
	FVector Corner3;
	FVector Corner4;
	FVector Corner5;
	FVector Corner6;
	FVector Corner7;
	FVector Corner8;
	UPROPERTY(Replicated)
	class AUnbuiltBuilding* Building;
	class AOverseerer* _overseerer;
};
