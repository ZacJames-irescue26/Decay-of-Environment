// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBuildingBTTask.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BTNode.h>
#include "../EnemyAIController.h"

USpawnBuildingBTTask::USpawnBuildingBTTask()
{
	NodeName = TEXT("Spawn Building");
}

EBTNodeResult::Type USpawnBuildingBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	if (MyController->GameInstance->EnemyComponentValue >= 10)
	{
		const FVector TargetLocation = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
		FRotator Rotation = { 0,0,0 };
		ABuilding* Building = GetWorld()->SpawnActor<ABuilding>(BuildingToSpawn, TargetLocation, Rotation);
		if (Building != nullptr)
		{
			Building->SetPlayerOwner(-1);
			Building->SetPlayerTeam(-1);
		
			MyController->GameInstance->EnemyBuildings.Add(Building);
			MyController->GameInstance->EnemyComponentValue -= 10;
		}

	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString USpawnBuildingBTTask::GetStaticDescription() const
{
	return FString::Printf(TEXT("Spawn buildign at: %s"), * BlackboardKey.SelectedKeyName.ToString());
}

