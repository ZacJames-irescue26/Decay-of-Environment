// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBuildingBTTask.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/BTNode.h>

USpawnBuildingBTTask::USpawnBuildingBTTask()
{

}

EBTNodeResult::Type USpawnBuildingBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	AAIController* MyController = OwnerComp.GetAIOwner();

	const FVector TargetLocation = MyBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
	FRotator Rotation = { 0,0,0 };
	ABuilding* Building = GetWorld()->SpawnActor<ABuilding>(BuildingToSpawn, TargetLocation, Rotation);
	Building->IsPlaced = true;
	Building->SetPlayerOwner(-1);
	Building->SetPlayerTeam(-1);
	
	return EBTNodeResult::Succeeded;
}

FString USpawnBuildingBTTask::GetStaticDescription() const
{
	return FString::Printf(TEXT("Spawn buildign at: %s"), * BlackboardKey.SelectedKeyName.ToString());
}

