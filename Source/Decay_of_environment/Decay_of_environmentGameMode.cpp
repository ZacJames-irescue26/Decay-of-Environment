// Copyright Epic Games, Inc. All Rights Reserved.

#include "Decay_of_environmentGameMode.h"
#include "Decay_of_environmentPlayerController.h"
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


//APlayerController* ADecay_of_environmentGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
//{
//	//UWorld* World = GetWorld();
//	//if (!ensure(World != nullptr)) return nullptr;
//	//ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(World->GetFirstPlayerController());
//	//NewPlayer->PlayerController = PlayerController;
//	//return Cast<APlayerController>(NewPlayer->PlayerController->GetLocalPlayer());
//	//UE_LOG(LogTemp, Warning, TEXT("Error message: %s"), *ErrorMessage)
//	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
//	if (PlayerControllerBPClass.Class != NULL)
//	{
//		PlayerControllerClass = PlayerControllerBPClass.Class;
//	}
//	//auto Player = NewPlayer->PlayerController->GetClass() = PlayerControllerBPClass.Class;
//	NewPlayer = ADecay_of_environmentPlayerController::StaticClass();
//	NewPlayer = PlayerControllerBPClass.Class;
//	return NewPlayer;
//}

void ADecay_of_environmentGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	//UWorld* World = GetWorld();
	//if (!ensure(World != nullptr)) return;
	//ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(World->GetFirstPlayerController());
	//NewPlayer->Player->PlayerController = PlayerController;

	Players.Add(Cast<ADecay_of_environmentPlayerController>(NewPlayer));
	UE_LOG(LogTemp, Warning, TEXT("Added Player"));
}

void ADecay_of_environmentGameMode::Logout(AController* Exiting)
{
	Players.Remove(Cast<ADecay_of_environmentPlayerController>(Exiting));
	UE_LOG(LogTemp, Warning, TEXT("Removing player"));
}

void ADecay_of_environmentGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		//PlayerControllerClass = PlayerControllerBPClass.Class;
		//NewPC->SetClass(PlayerControllerBPClass.Class);
	}
	Players.Add(Cast<ADecay_of_environmentPlayerController>(NewPC));
}
