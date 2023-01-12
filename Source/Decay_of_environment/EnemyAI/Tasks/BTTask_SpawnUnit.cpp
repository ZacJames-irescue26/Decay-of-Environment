// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnUnit.h"
#include "../EnemyAIController.h"
#include <UObject/PropertyAccessUtil.h>
#include <UObject/ConstructorHelpers.h>

UBTTask_SpawnUnit::UBTTask_SpawnUnit()
{
	NodeName = TEXT("Spawn Unit");
}

EBTNodeResult::Type UBTTask_SpawnUnit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	for (auto Building : MyController->GameInstance->EnemyBuildings)
	{
		if (MyController->GameInstance->EnemyComponentValue >= 10)
		{
			if (Building->IsMainBuilding)
			{
				FVector Location = Building->GetActorLocation();
				Location.X = Location.X + 20;
				UE_LOG(LogTemp, Warning, TEXT("Spawned at X: %d Y: %d"), Location.X, Location.Y);
				FRotator Rotation = { 0,0,0 };
				ADecay_of_environmentCharacter* Unit = GetWorld()->SpawnActor<ADecay_of_environmentCharacter>(UnitToSpawn, Location, Rotation);
				if (Unit != nullptr)
				{
					Unit->SetPlayerOwner(-1);
					Unit->SetPlayerTeam(-1);
					MyController->GameInstance->EnemyUnits.Add(Unit);
					MyController->GameInstance->EnemyComponentValue -= 10;
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;

				}
			}

		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SpawnUnit::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}
