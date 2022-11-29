// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums_Structs.h"
#include "CharacterDetails.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UCharacterDetails : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Character Stats")
	float GetHealth();

	FCharacterStats GetStats() const { return stats; }
	void SetStats(FCharacterStats val) { stats = val; }
private:
	FCharacterStats stats;

};
