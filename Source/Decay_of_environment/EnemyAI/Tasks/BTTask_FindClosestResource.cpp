// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindClosestResource.h"
#include "../../ResourceInterface.h"
#include "../EnemyAIController.h"
#include <Kismet/GameplayStatics.h>
#include "../../Decay_of_environmentCharacter.h"


UBTTask_FindClosestResource::UBTTask_FindClosestResource()
{
	NodeName = TEXT("Find Closest Resources");
}

EBTNodeResult::Type UBTTask_FindClosestResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UResourceInterface::StaticClass(), ResourceActors);
	MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	AActor* ClosestResource = FindClosestResource(Character, ResourceActors);
	if (ClosestResource != nullptr)
	{
		MyController->SetTargetActor(ClosestResource);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

}
bool UBTTask_FindClosestResource::FindResource(EResourceType resType, TArray<AActor*> actors) {
	bool resFound = false;

	for (AActor* res : actors) {
		IResourceInterface* resi = Cast<IResourceInterface>(res);

		if (resi != NULL && resi->GetType() == resType && resi->GetAmount() > 0 && !res->IsUnreachable()) {
			MyController->SetTargetActor(res);
			resFound = true;
			break;
		}
	}

	return resFound;
}

AActor* UBTTask_FindClosestResource::FindClosestResource(ADecay_of_environmentCharacter* Character, TArray<AActor*> _ResourceActors)
{
	if (_ResourceActors.Num() > 0)
	{
		AActor* Closest = _ResourceActors[0];
		for (AActor* Resource : _ResourceActors)
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