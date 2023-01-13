// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DepositResources.h"
#include <Kismet/GameplayStatics.h>
#include "../EnemyAIController.h"
#include "../../Enums_Structs.h"

UBTTask_DepositResources::UBTTask_DepositResources()
{
	NodeName = TEXT("Deposit Resources");
}

EBTNodeResult::Type UBTTask_DepositResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	TArray<AActor*> storageActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UStorageInterface::StaticClass(), storageActors);
	AActor* ClosestBase = FindClosestBase(Character, storageActors);
	if (ClosestBase != nullptr)
	{
		MyController->MoveToActor(ClosestBase);
		for (FItem& item : MyController->GetRTSCharacter()->GetStats().inventory.items)
		{
			MyController->GameInstance->EnemyComponentValue += item.amount;
		}
		MyController->GetRTSCharacter()->GetStats().inventory.items.Empty();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Succeeded;
}

FString UBTTask_DepositResources::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}

AActor* UBTTask_DepositResources::FindClosestBase(ADecay_of_environmentCharacter* Character, TArray<AActor*> _storageActors)
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
