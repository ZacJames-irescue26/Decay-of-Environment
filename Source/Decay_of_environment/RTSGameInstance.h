// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/Engine.h"
#include "UI/UserInterface.h"
#include "MenuSystem/ManuInterface.h"
#include "MenuSystem/MainMenu.h"
#include "OnlineSubsystem.h"
#include <OnlineSessionSettings.h>
#include <Templates/SharedPointer.h>
#include "OnlineSessionSettings.h"
#include <Interfaces/OnlineSessionInterface.h>
#include <AIController.h>
#include <GameFramework/Controller.h>
#include "RTSGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FCharacterSaveData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		FTransform Transform;
	UPROPERTY(EditAnywhere)
		FVector Position;
	UPROPERTY(EditAnywhere)
		AActor* TargetActor;
	UPROPERTY(EditAnywhere)
		int32 team;
	UPROPERTY(EditAnywhere)
		int32 Owner;
	UPROPERTY(EditAnywhere)
		int32 UnitTypeId;
};

USTRUCT(BlueprintType)
struct FBuildingSaveData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		FTransform Transform;
	UPROPERTY(EditAnywhere)
		FVector Position;
	UPROPERTY(EditAnywhere)
		int32 team;
	UPROPERTY(EditAnywhere)
		int32 Owner;
	UPROPERTY(EditAnywhere)
		int32 BuildingTypeId;
};

/**
 * 
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API URTSGameInstance : public UGameInstance, public IManuInterface
{
	GENERATED_BODY()
public:

	URTSGameInstance(const FObjectInitializer& ObjectInitializer);
	int32 EnemyComponentValue = 100;
	UPROPERTY(EditAnywhere)
	TArray<ABuilding*> EnemyBuildings;
	TArray<FNavLocation> Waypoint;
	TArray<ADecay_of_environmentCharacter*> EnemyUnits;
public:
		virtual void Init();
		
		UFUNCTION(Exec)
		void Host(FString Servername) override;

		UFUNCTION(Exec)
		void Join(uint32 Index) override;

		void StartSession();

		UFUNCTION(BlueprintCallable)
		void LoadMenuWidget();

		UFUNCTION(BlueprintCallable)
		void InGameLoadMenu();

		virtual void LoadMainMenu() override;
		void SaveGame();
		void LoadGame();
		void RefreshServerList() override;

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;
	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void HandleNetworkFailure(UWorld* World, class UNetDriver* InNetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
	void CreateSession();

	FString DesiredServerName;

	/**************Spawning Actors******************/
	TSubclassOf<AActor> CharacterSpawn;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DefaultCharacter;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DefaultBuilding;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Base;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Army;
	/***************Spawning Enemies***************************/
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EnemyCharacter;
};

