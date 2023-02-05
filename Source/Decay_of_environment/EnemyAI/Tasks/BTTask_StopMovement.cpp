// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StopMovement.h"
#include "../EnemyAIController.h"


UBTTask_StopMovement::UBTTask_StopMovement()
{
	NodeName = TEXT("Stop Movement");
}

EBTNodeResult::Type UBTTask_StopMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	MyController->StopMovement();
	return EBTNodeResult::Succeeded;

}
