// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NextWaypoint.h"
#include "../EnemyAIController.h"
#include "../../Decay_of_environmentCharacter.h"

UBTTask_NextWaypoint::UBTTask_NextWaypoint()
{
	NodeName = TEXT("Next Waypoint");
}

EBTNodeResult::Type UBTTask_NextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	if (Character->WaypointCounter < Character->Waypoints.Num())
	{
		Character->WaypointCounter++;
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
	
}
