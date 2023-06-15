// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamagableInterface.h"
#include "TeamInterface.h"
#include "Building.h"
#include "DamagableInterface.h"
#include "TeamInterface.h"
#include "BuidlingInterface.h"
#include "UnbuiltBuilding.generated.h"
UCLASS()
class DECAY_OF_ENVIRONMENT_API AUnbuiltBuilding : public ABuilding
{
GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnbuiltBuilding();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartTimer();
	void PauseTimer();
	UFUNCTION(Server, Reliable)
	void Server_SpawnBuilding();
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnBuilding();
	void SpawnBuilding();
private:
	float BuildTimer = 100.0f;
	float CurrentTime = 0.0f;
	FTimerHandle BuildTimerhandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABuilding> BuildingToSpawn;
	UPROPERTY(VisibleAnywhere)
	bool isPaused = false;
	UPROPERTY(Replicated)
	class ABuilding* _Building;
};
