// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToWaypoint.h"
#include "../EnemyAIController.h"
#include <NavigationSystem.h>
#include "../../Decay_of_environmentCharacter.h"


UBTTask_MoveToWaypoint::UBTTask_MoveToWaypoint()
{
	NodeName = TEXT("Move to Waypoint");
}

EBTNodeResult::Type UBTTask_MoveToWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	
	FNavLocation Location{};

	// Get AI Pawn
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	//Get Pawn Origin
	const FVector Origin = AIPawn->GetActorLocation();
	
	if (Character->WaypointCounter < Character->Waypoints.Num())
	{
		MyController->MoveToLocation(Character->Waypoints[Character->WaypointCounter]);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Succeeded;

	//MyController->GameInstance->Waypoint.Add(FNavLocation(FVector(380.0, -150.0, 110.0)));
	//MyController->GameInstance->Waypoint.Add(FNavLocation(FVector(400.0, -150.0, 110.0)));
	//MyController->GameInstance->Waypoint.Add(FNavLocation(FVector(500.0, -150.0, 110.0)));
	//const UNavigationSystemV1* NavSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };
	//if (IsValid(NavSystem))
	//{

	//	MyController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, MyController->GameInstance->Waypoint[1].Location);
	//	//FNavLocation EnemyLocation	= FNavLocation( FVector(220.0, 1170.0, 416.0 ));
	//	//AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, EnemyLocation.Location);
	//}
	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//return EBTNodeResult::Succeeded;
}

FString UBTTask_MoveToWaypoint::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}
