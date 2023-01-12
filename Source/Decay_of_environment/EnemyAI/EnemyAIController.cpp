// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "../Decay_of_environmentCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <UObject/ConstructorHelpers.h>
#include "../RTSGameInstance.h"



AEnemyAIController::AEnemyAIController()
{
	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour tree component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard component"));

}
void AEnemyAIController::BeginPlay()
{
	GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	Super::BeginPlay();


	if (IsValid(BehaviourTree))
	{
		RunBehaviorTree(BehaviourTree);
		BehaviourTreeComponent->StartTree(*BehaviourTree);
	}
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADecay_of_environmentCharacter::StaticClass(), Actors);
	for (auto a : Actors)
	{
		ADecay_of_environmentCharacter* c = Cast<ADecay_of_environmentCharacter>(a);
		if (c->GetPlayerOwner() == -1)
		{
			GameInstance->EnemyUnits.Add(c);
		}
	}
	TArray<AActor*> Buildings;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuilding::StaticClass(), Buildings);
	for (auto b : Buildings)
	{
		ABuilding* c = Cast<ABuilding>(b);
		if (c->GetPlayerOwner() == -1)
		{
			GameInstance->EnemyBuildings.Add(c);
		}
	}

}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(Blackboard) && IsValid(BehaviourTree))
	{
		Blackboard->InitializeBlackboard(*BehaviourTree->BlackboardAsset);
	}
}

ADecay_of_environmentCharacter* AEnemyAIController::GetRTSCharacter()
{
	if (rtsCharacter == nullptr)
	{
		rtsCharacter = Cast<ADecay_of_environmentCharacter>(GetCharacter());
	}
	return rtsCharacter;
}

void AEnemyAIController::SetTargetActor(AActor* val)
{
	previousTarget = targetActor;
	targetActor = val;
}
