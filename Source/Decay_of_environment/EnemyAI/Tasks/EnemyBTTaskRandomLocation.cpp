// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBTTaskRandomLocation.h"
#include <GameFramework/Pawn.h>
#include <AIController.h>
#include <NavigationSystem.h>
#include <BehaviorTree/BlackboardComponent.h>

UEnemyBTTaskRandomLocation::UEnemyBTTaskRandomLocation()
{
	NodeName = TEXT("Find Random location");

	//accept only vectors

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UEnemyBTTaskRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UEnemyBTTaskRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};

	// Get AI Pawn
	AAIController* AIController {OwnerComp.GetAIOwner()};
	const APawn* AIPawn {AIController->GetPawn()};

	//Get Pawn Origin
	const FVector Origin = AIPawn->GetActorLocation();

	const UNavigationSystemV1* NavSystem {UNavigationSystemV1::GetCurrent(GetWorld())};
	if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
		//FNavLocation EnemyLocation	= FNavLocation( FVector(220.0, 1170.0, 416.0 ));
		//AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, EnemyLocation.Location);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}

FString UEnemyBTTaskRandomLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
