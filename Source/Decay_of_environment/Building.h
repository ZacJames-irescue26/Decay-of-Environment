// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums_Structs.h"
#include "DamagableInterface.h"
#include "StorageInterface.h"
#include "TeamInterface.h"
#include "BuidlingInterface.h"
#include "Building.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API ABuilding : public AActor, public IDamagableInterface, public ITeamInterface, public IBuidlingInterface
{
	GENERATED_BODY()
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	bool IsMainBuilding = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "stats", Replicated)
	FBuildingStats buildingStats;
	
	FVector mPos;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void TakeDamage(float damage) override;
	virtual float GetHealth()override;
	virtual float GetMaxHealth() override;
	UFUNCTION(Server, Reliable)
	virtual void Server_TakeDamage(float damage) override;
	virtual int32 GetPlayerTeam() override;
	virtual int32 GetPlayerOwner() override;
	virtual void SetPlayerTeam(int32 Value) override;
	virtual void SetPlayerOwner(int32 Value) override;
public:
	FBuildingStats GetBuildingStats() const { return buildingStats; }
	void SetBuildingStats(FBuildingStats val) { buildingStats = val; }
	UDecalComponent* Decal;


};
