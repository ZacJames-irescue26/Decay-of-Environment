// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "StorageInterface.h"
#include "Base.generated.h"

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API ABase : public ABuilding, public IStorageInterface
{
	GENERATED_BODY()
	ABase();
};
