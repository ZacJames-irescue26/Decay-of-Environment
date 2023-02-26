// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dash.h"
#include "ShieldAblitity.h"
#include "../Decay_of_environmentCharacter.h"
#include "../Decay_of_environmentPlayerController.h"
#include "AbilityManager.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API AAbilityManager : public AActor, public ADecay_of_environmentPlayerController
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DashAbility(TArray<ADecay_of_environmentCharacter*> selectedUnits);
	void Shield(TArray<ADecay_of_environmentCharacter*> selectedUnits);
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADash> Dash;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AShieldAblitity> AbilityToSpawn;
};
