// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Timer.h"


UBTTask_Timer::UBTTask_Timer()
{
	NodeName = "SetTimer";
}

EBTNodeResult::Type UBTTask_Timer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	GetWorld()->GetTimerManager().SetTimer(MyController->ActionRate, this, &UBTTask_Timer::CanPerformActions, MyController->actionDelay);
	return EBTNodeResult::Succeeded;
}

void UBTTask_Timer::CanPerformActions()
{
	MyController->canPerformActions = true;
}
