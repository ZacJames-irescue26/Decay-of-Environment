// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PawnLocation.h"
#include "../EnemyAIController.h"

EBTNodeResult::Type UBTTask_PawnLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Pawn
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	const APawn* AIPawn{ MyController->GetPawn() };

	//Get Pawn Origin
	FNavLocation Origin = FNavLocation(FVector(AIPawn->GetActorLocation()));
	MyController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Origin.Location);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_PawnLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}