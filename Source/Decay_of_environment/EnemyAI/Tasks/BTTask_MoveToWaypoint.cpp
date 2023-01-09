// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToWaypoint.h"

EBTNodeResult::Type UBTTask_MoveToWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	FNavLocation endPosi = FNavLocation(startPosi);
	return EBTNodeResult::Succeeded
}

FString UBTTask_MoveToWaypoint::GetStaticDescription() const
{

}
