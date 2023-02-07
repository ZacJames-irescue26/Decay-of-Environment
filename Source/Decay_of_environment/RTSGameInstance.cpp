// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"

//#include "PlatformTrigger.h"
#include "MenuSystem/MenuWidget.h"

#include "Interfaces/OnlineSessionInterface.h"
#include <GameFramework/PlayerController.h>
#include "MenuSystem/MainMenu.h"
#include "SaveLoadSystem/TestSaveGame.h"
#include <Kismet/GameplayStatics.h>
#include "Enums_Structs.h"
#include "BaseAI.h"
#include "EnemyAI/EnemyAIController.h"

const static FName SESSION_NAME = TEXT("GameSession");
const static FName Server_NAME_SETTINGS_KEY = TEXT("ServerName");

URTSGameInstance::URTSGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/TopDown/Blueprints/MenuSystem/BP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/TopDown/Blueprints/MenuSystem/BP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;

	InGameMenuClass = InGameMenuBPClass.Class;
	//UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuBPClass.Class->GetName());
}
void URTSGameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session interface"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &URTSGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &URTSGameInstance::OnDestroySessionComplete);

			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &URTSGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &URTSGameInstance::OnJoinSessionComplete);



		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
	if (GEngine != nullptr)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &URTSGameInstance::HandleNetworkFailure);
	}
}
void URTSGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not create session"));
		return;
	}
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;
	world->ServerTravel("/Game/TopDown/Maps/Tilegrid?listen");
}

void URTSGameInstance::Host(FString Servername)
{
	DesiredServerName = Servername;
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}

	}


}
void URTSGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}
void URTSGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			SessionSettings.bIsLANMatch = true;
		}
		else
		{
			SessionSettings.bIsLANMatch = false;
		}


		SessionSettings.NumPublicConnections = 5;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.bUseLobbiesIfAvailable = true;
		SessionSettings.Set(Server_NAME_SETTINGS_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);

	}

}

void URTSGameInstance::OnFindSessionComplete(bool Success)
{


	if (Success && SessionSearch.IsValid() && Menu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finish Find Session"));

		TArray<FServerData> ServerNames;
		for (auto& SearchResult : SessionSearch->SearchResults)
		{
			FServerData Data;

			Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
			Data.CurrentPlayers = Data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
			Data.HostUsername = SearchResult.Session.OwningUserName;
			FString ServerName;
			if (SearchResult.Session.SessionSettings.Get(Server_NAME_SETTINGS_KEY, ServerName))
			{
				UE_LOG(LogTemp, Warning, TEXT("Data Found in settings %s"), *ServerName);
				Data.Name = ServerName;
			}
			else
			{
				Data.Name = "could not find server name";
				UE_LOG(LogTemp, Warning, TEXT("Didnt find settings"));
			}
			UE_LOG(LogTemp, Warning, TEXT("Found Session Names: %s"), *SearchResult.GetSessionIdStr());
			ServerNames.Add(Data);
		}
		Menu->SetServerList(ServerNames);
	}

}

void URTSGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string"));
		return;
	}
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void URTSGameInstance::HandleNetworkFailure(UWorld* World, class UNetDriver* InNetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	LoadMainMenu();
}

void URTSGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}



void URTSGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
	if (!SessionSearch.IsValid())
	{
		return;
	}

	if (Menu != nullptr)
	{
		Menu->Teardown();
	}
	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);




}

void URTSGameInstance::StartSession()
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->StartSession(SESSION_NAME);
	}
}

void URTSGameInstance::LoadMenuWidget()
{
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void URTSGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	UMenuWidget* _Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(_Menu != nullptr)) return;

	_Menu->Setup();
	_Menu->SetMenuInterface(this);
}

void URTSGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/TopDown/Blueprints/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void URTSGameInstance::SaveGame()
{
	TArray<AActor*> AllCharacters;
	TArray<AActor*> AllBuildings;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADecay_of_environmentCharacter::StaticClass(), AllCharacters);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuilding::StaticClass(), AllBuildings);
	
	UTestSaveGame* SaveGameInstance = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));
	
	for (AActor* a : AllCharacters)
	{
		ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(a);

		FCharacterSaveData save;
		save.Name = Character->GetName();
		save.Position = Character->GetActorLocation();
		save.Transform = Character->GetTransform();
		//save.TargetActor = Character->GetController()->
		save.Owner = Character->stats.owner;
		save.team = Character->stats.team;
		save.UnitTypeId = Character->stats.unitID;
		if (save.Owner < 0)
		{
			/*Character->AIControllerClass = AEnemyAIController::StaticClass();*/

			/*AEnemyAIController* EnemeyController = Cast<AEnemyAIController>(Character->AIControllerClass);
			if (EnemeyController == nullptr)
			{
				return;
			}
			save.TargetActor = EnemeyController->GetTargetActor();*/
		}
		else
		{
			/*Character->AIControllerClass = ABaseAI::StaticClass();
			ABaseAI* AIController = Cast<ABaseAI>(Character->AIControllerClass);
			if (AIController == nullptr)
			{
				return;
			}
			save.TargetActor = AIController->GetTargetActor();*/
		}
		//save.controller = Character->AIControllerClass;

		SaveGameInstance->SaveCharacter.Add(save);
	}
	for (AActor* a : AllBuildings)
	{
		
		ABuilding* Building = Cast<ABuilding>(a);
		FBuildingSaveData save;
		save.Name = Building->GetName();
		save.Position = Building->GetActorLocation();
		save.BuildingTypeId = Building->buildingStats.BuildingTypeId;
		save.Transform = Building->GetTransform();
		save.Owner = Building->buildingStats.owner;
		save.team = Building->buildingStats.team;
		SaveGameInstance->SaveBuildings.Add(save);
	}
	SaveGameInstance->TestSave = 10;
	SaveGameInstance->Test = 30;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("TestSlot"), 0);

}
void URTSGameInstance::LoadGame()
{
	UTestSaveGame* SaveGameInstance = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));
	SaveGameInstance = Cast<UTestSaveGame>(UGameplayStatics::LoadGameFromSlot("TestSlot", 0));
	TArray<AActor*> AllCharacters;
	TArray<AActor*> AllBuildings;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADecay_of_environmentCharacter::StaticClass(), AllCharacters);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuilding::StaticClass(), AllBuildings);
	for (AActor* a : AllCharacters)
	{
		a->Destroy(true);
	}
	for (AActor* a : AllBuildings)
	{
		a->Destroy(true);
	}

	for (FCharacterSaveData character : SaveGameInstance->SaveCharacter)
	{
		
		if (character.Owner < 0)
		{
			;
			switch (character.UnitTypeId)
			{
			case 0:
				CharacterSpawn = EnemyCharacter;
				break;
			default:
				break;
			}
			ADecay_of_environmentCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ADecay_of_environmentCharacter>(CharacterSpawn, character.Position, FRotator::ZeroRotator);
			SpawnedCharacter->stats.team = character.team;
			SpawnedCharacter->stats.owner = character.Owner;
			/*	AEnemyAIController* EnemyController =Cast<AEnemyAIController>(SpawnedCharacter->AIControllerClass);
				EnemyController->SetTargetActor(character.TargetActor);*/
		}
		else
		{
			switch (character.UnitTypeId)
			{
			case 0:
				CharacterSpawn = DefaultCharacter;
				break;
			case 1: 
				CharacterSpawn = Army;
			default:
				break;
			}
			ADecay_of_environmentCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ADecay_of_environmentCharacter>(CharacterSpawn, character.Position, FRotator::ZeroRotator);
			SpawnedCharacter->stats.team = character.team;
			SpawnedCharacter->stats.owner = character.Owner;
			/*ABaseAI* AIController = Cast<ABaseAI>(SpawnedCharacter->AIControllerClass);
			AIController->SetTargetActor(character.TargetActor);*/
			
		}

	}
	for (FBuildingSaveData Building : SaveGameInstance->SaveBuildings)
	{
		TSubclassOf<AActor> ActorToSpawn;
		switch (Building.BuildingTypeId)
		{
		case 0:
			ActorToSpawn = DefaultBuilding;
			
			break;
		case 1:
			ActorToSpawn = Base;
			break;
		default:
			break;
		}
		ABuilding* NewBuilding = GetWorld()->SpawnActor<ABuilding>(ActorToSpawn, Building.Position, FRotator::ZeroRotator);
		NewBuilding->IsPlaced = true;
		NewBuilding->buildingStats.owner = Building.Owner;
		NewBuilding->buildingStats.team = Building.team;
		
	}
	

}

