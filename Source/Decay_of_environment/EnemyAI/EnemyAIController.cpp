// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "../Decay_of_environmentCharacter.h"
#include <Kismet/GameplayStatics.h>

AEnemyAIController::AEnemyAIController()
{
	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour tree component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard component"));
}
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BehaviourTree))
	{
		RunBehaviorTree(BehaviourTree);
		BehaviourTreeComponent->StartTree(*BehaviourTree);
	}
	//TArray<AActor*> Actors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADecay_of_environmentCharacter::StaticClass(), Actors);
	//for (auto a : Actors)
	//{
	//	ADecay_of_environmentCharacter* c = Cast<ADecay_of_environmentCharacter>(a);
	//	if (c->GetPlayerOwner() == -1)
	//	{
	//		EnemyArray.Add(c);
	//		/*AEnemyAIController* con = Cast<AEnemyAIController>(c->GetController());
	//		con->MoveToLocation(FVector(220.0, 1170.0, 416.0));*/
	//		UE_LOG(LogTemp, Warning, TEXT("Added enemy"));
	//	}
	//}

}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(Blackboard) && IsValid(BehaviourTree))
	{
		Blackboard->InitializeBlackboard(*BehaviourTree->BlackboardAsset);
	}
}
