// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsAtWaypoint.h"
#include "../EnemyAIController.h"
#include "../../Decay_of_environmentCharacter.h"

UBTDecorator_IsAtWaypoint::UBTDecorator_IsAtWaypoint()
{
	NodeName = "Is at waypoint";
}

bool UBTDecorator_IsAtWaypoint::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	if (Character->WaypointCounter >= Character->Waypoints.Num())
	{
		return false;
	}
	float dist = FVector::Distance(MyController->GetCharacter()->GetActorLocation(), Character->Waypoints[Character->WaypointCounter]);

	if (dist < (Character->stats.AttackRange))
	{
		return true;
	}
	return false;
}

