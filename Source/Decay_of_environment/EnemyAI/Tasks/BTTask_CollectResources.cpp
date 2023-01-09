// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CollectResources.h"
#include "../EnemyAIController.h"

EBTNodeResult::Type UBTTask_CollectResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	MyController->MoveToLocation(FVector(380.0, -150.0, 110.0));
	return EBTNodeResult::Succeeded;
}

FString UBTTask_CollectResources::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}
