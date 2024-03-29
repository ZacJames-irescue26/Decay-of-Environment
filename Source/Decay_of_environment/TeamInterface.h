// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TeamInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeamInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DECAY_OF_ENVIRONMENT_API ITeamInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual int32 GetPlayerTeam();
	virtual int32 GetPlayerOwner();
	virtual void SetPlayerTeam(int32 Value) = 0;
	virtual void SetPlayerOwner(int32 Value) = 0;
};
