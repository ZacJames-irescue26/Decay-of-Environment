// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums_Structs.h"
#include "StorageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStorageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DECAY_OF_ENVIRONMENT_API IStorageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TArray<FItem>& GetItems();
	virtual void AddItem(FString name, int32 amount);
	virtual void RemoveItem(FString name, int32 amount);
protected:
	FInventory inventory;
};
