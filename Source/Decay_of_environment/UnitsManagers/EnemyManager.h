// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Decay_of_environment/Decay_of_environmentCharacter.h"
#include "EnemyManager.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnWave(FVector Spawnposition, TMap<int, EUnitClass> SpawnCharacters, TArray<FVector> Waypoints);

private:
	UPROPERTY(EditAnywhere)
	TArray<ADecay_of_environmentCharacter*> EnemyCharacters;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADecay_of_environmentCharacter> SpawnWorker;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADecay_of_environmentCharacter> SpawnArmy;

};
