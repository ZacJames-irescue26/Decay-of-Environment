// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToClass.h"
#include <AIController.h>
#include <NavigationSystem.h>
#include "../../Base.h"
#include <BehaviorTree/BlackboardComponent.h>
#include "../EnemyAIController.h"



UBTTask_MoveToClass::UBTTask_MoveToClass()
{
	NodeName = TEXT("Move To Class");

	//accept only objects

	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_MoveToClass, BlackboardKey), AActor::StaticClass());
	
}

EBTNodeResult::Type UBTTask_MoveToClass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation Location{};
	// Get AI Pawn
	AAIController* AIController{ OwnerComp.GetAIOwner() };
	AEnemyAIController* MyController = Cast<AEnemyAIController>(AIController);
	const APawn* AIPawn{ AIController->GetPawn() };

	//Get Pawn Origin
	const FVector Origin = AIPawn->GetActorLocation();

	const UNavigationSystemV1* NavSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };
	if (IsValid(NavSystem))
	{

		//AIController->GetBlackboardComponent()->SetValueAsClass(BlackboardKey.SelectedKeyName, Location.Location);
		AIController->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, MyController->GetTargetActor());

		//FNavLocation EnemyLocation	= FNavLocation( FVector(220.0, 1170.0, 416.0 ));
		//AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, EnemyLocation.Location);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

