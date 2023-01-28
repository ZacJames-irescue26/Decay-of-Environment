// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Decay_of_environmentCharacter.h"
#include "ShieldAblitity.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API AShieldAblitity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShieldAblitity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void SetParentActor(ADecay_of_environmentCharacter* _Parent);

	UFUNCTION()
	void DestroyShield();
	ADecay_of_environmentCharacter* Parent;

	FTimerHandle ShieldTimerHandle;
	float ShieldLifeTime;
};
