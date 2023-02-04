// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindBase.h"
#include "../../Decay_of_environmentCharacter.h"
#include "../EnemyAIController.h"
#include <Kismet/GameplayStatics.h>

UBTTask_FindBase::UBTTask_FindBase()
{
	NodeName = TEXT("Find Base");
}

EBTNodeResult::Type UBTTask_FindBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	TArray<AActor*> storageActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UStorageInterface::StaticClass(), storageActors);
	AActor* ClosestBase = FindClosestBase(Character, storageActors);
	MyController->SetTargetActor(ClosestBase);
	if (MyController->GetTargetActor() != nullptr)
	{
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

AActor* UBTTask_FindBase::FindClosestBase(ADecay_of_environmentCharacter* Character, TArray<AActor*> _storageActors)
{
	if (_storageActors.Num() > 0)
	{
		AActor* Closest = _storageActors[0];
		for (AActor* Resource : _storageActors)
		{
			float DistanceToClosest =
				(FMath::Square(Character->GetActorLocation().X) - FMath::Square(Closest->GetActorLocation().X)) +
				(FMath::Square(Character->GetActorLocation().Y) - FMath::Square(Closest->GetActorLocation().Y)) +
				(FMath::Square(Character->GetActorLocation().Z) - FMath::Square(Closest->GetActorLocation().Z));

			float DistanceToResource =
				(FMath::Square(Character->GetActorLocation().X) - FMath::Square(Resource->GetActorLocation().X)) +
				(FMath::Square(Character->GetActorLocation().Y) - FMath::Square(Resource->GetActorLocation().Y)) +
				(FMath::Square(Character->GetActorLocation().Z) - FMath::Square(Resource->GetActorLocation().Z));
			if (DistanceToClosest > DistanceToResource)
			{
				Closest = Resource;
			}
		}
		return Closest;
	}
	return nullptr;
}