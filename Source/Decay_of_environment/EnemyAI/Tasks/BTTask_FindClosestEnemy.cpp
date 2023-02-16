// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindClosestEnemy.h"
#include "../EnemyAIController.h"
#include "../../Decay_of_environmentCharacter.h"

UBTTask_FindClosestEnemy::UBTTask_FindClosestEnemy()
{
	NodeName = TEXT("Find Closest Enemy");
}

EBTNodeResult::Type UBTTask_FindClosestEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	TArray<AActor*> OverlappingActors;
	Character->GetOverlappingActors(OverlappingActors, ADecay_of_environmentCharacter::StaticClass());
	for (AActor* a : OverlappingActors)
	{
		ADecay_of_environmentCharacter* c = Cast<ADecay_of_environmentCharacter>(a);
		MyController->SetTargetActor(c);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
