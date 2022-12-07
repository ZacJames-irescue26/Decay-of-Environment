// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Decay_of_environmentPlayerController.h"
#include "Decay_of_environmentGameMode.generated.h"

UCLASS(minimalapi)
class ADecay_of_environmentGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADecay_of_environmentGameMode();
	//virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;
	TArray<ADecay_of_environmentPlayerController*>Players;
};



