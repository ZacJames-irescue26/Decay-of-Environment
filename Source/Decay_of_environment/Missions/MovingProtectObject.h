// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Decay_of_environment/Decay_of_environmentCharacter.h"
#include "MovingProtectObject.generated.h"

class AProtectObjectiveAI;

UCLASS()
class DECAY_OF_ENVIRONMENT_API AMovingProtectObject : public ADecay_of_environmentCharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingProtectObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TArray<AActor*> CloseActors;
	AProtectObjectiveAI* con;
};
