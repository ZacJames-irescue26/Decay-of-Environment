// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Decay_of_environmentCharacter.h"
#include "../Decay_of_environmentPlayerController.h"
#include "Dash.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API ADash : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADash();
	void SetParentActor(ADecay_of_environmentCharacter* _Parent);
	void DestroyDash();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ADecay_of_environmentCharacter* Parent;
	FVector MousePos;
	FRotator rotation;
	ADecay_of_environmentPlayerController* PlayerController;
	FVector Difference;
	FRotator _rotation;
};
