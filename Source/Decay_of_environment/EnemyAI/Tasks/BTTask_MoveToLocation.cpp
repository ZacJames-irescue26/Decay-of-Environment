// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToLocation.h"
#include "../EnemyAIController.h"

UBTTask_MoveToLocation::UBTTask_MoveToLocation()
{
	NodeName = TEXT("Move To Location");
}

EBTNodeResult::Type UBTTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController{ OwnerComp.GetAIOwner() };
	AEnemyAIController* MyController = Cast<AEnemyAIController>(AIController);
	const APawn* AIPawn{ AIController->GetPawn() };

	MyController->MoveToActor(MyController->GetTargetActor());
	return EBTNodeResult::Succeeded;

}
