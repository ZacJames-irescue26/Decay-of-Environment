// Copyright Epic Games, Inc. All Rights Reserved.

#include "Decay_of_environmentGameMode.h"
#include "Decay_of_environmentPlayerController.h"
#include "DOEPlayerState.h"
#include "Decay_of_environmentCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Engine/World.h>
#include <UObject/UObjectBase.h>

ADecay_of_environmentGameMode::ADecay_of_environmentGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADecay_of_environmentPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/Overseerer_BP"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}


void ADecay_of_environmentGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ADOEPlayerState* DOEPlayerState = NewPlayer->GetPlayerState<ADOEPlayerState>();
	//DOEPlayerState->PlayerOwner = NumPlayers;
	DOEPlayerState->Server_SetPlayerOwner(NumPlayers - 1);
	UE_LOG(LogTemp, Warning, TEXT("Num of players %i"), NumPlayers);

	
	UE_LOG(LogTemp, Warning, TEXT("Added Player"));
}

void ADecay_of_environmentGameMode::Logout(AController* Exiting)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Removing player"));
}
