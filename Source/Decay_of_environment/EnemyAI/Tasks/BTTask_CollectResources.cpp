// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CollectResources.h"
#include "../EnemyAIController.h"
#include "../../ResourceInterface.h"
#include "../../DamagableInterface.h"
#include "../../Enums_Structs.h"
#include <Kismet/GameplayStatics.h>
#include <Math/UnrealMathUtility.h>

#define MIN(a,b)(a<b)?(a):(b)
#define MAX(a,b)(a>b)?(a):(b)

UBTTask_CollectResources::UBTTask_CollectResources()
{
	NodeName = TEXT("Collect Resources");
}

EBTNodeResult::Type UBTTask_CollectResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	//MyController->MoveToLocation(FVector(380.0, -150.0, 110.0));
	//IResourceInterface* ri = Cast<IResourceInterface>(GetTargetActor());
	int32 amount;
	
	
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UResourceInterface::StaticClass(), ResourceActors);

	// Does the target have resources left
	AActor* ClosestResource = FindClosestResource(Character, ResourceActors);
	if (MyController->GetRTSCharacter()->GetStats().unitID != 0)
	{
		return EBTNodeResult::Failed;
	}
	if (ClosestResource != nullptr)
	{
		IResourceInterface* ri = Cast<IResourceInterface>(ClosestResource);
		int32 space = MyController->GetRTSCharacter()->GetCarryWeight() - MyController->GetRTSCharacter()->GetWeight(); 
		amount = ri->GetAmount();
		if (amount > 0)
		{
			// Do we have carry space left
			if (space > 0)
			{

				// Find the lowest amount to gather, either the resources has less than we can carry / gather or we lack the space to gather fully
				MyController->MoveToActor(ClosestResource);
				int32 amountToTake = MIN(amount, space);
				amountToTake = MIN(MyController->GetRTSCharacter()->GetGatherAmount(), amountToTake);

				ri->TakeResources(amountToTake);
				MyController->GetRTSCharacter()->RecieveResources(amountToTake, ri);
			}
			// We ran out of space so return to storage
			else {
				return EBTNodeResult::Succeeded;
			}
		}
		// The target ran out of resources, but we still have carry space
		else if (space > 0) {
			/*TArray<AActor*> resourceActors;

			GetNearbyActors(resourceActors);*/
			//ShuffleArray<AActor*>(resourceActors);

			bool resFound = FindResource(ri->GetType(), ResourceActors);

			if (ResourceActors.Num() == 0 || !resFound) {
				return EBTNodeResult::Succeeded;
			}
		}
		// We ran out of space so return to storage
		else {
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Succeeded;
}


FString UBTTask_CollectResources::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}

bool UBTTask_CollectResources::FindResource(EResourceType resType, TArray<AActor*> actors) {
	bool resFound = false;

	for (AActor* res : actors) {
		IResourceInterface* resi = Cast<IResourceInterface>(res);

		if (resi != NULL && resi->GetType() == resType && resi->GetAmount() > 0 && !res->IsUnreachable()) {
			//SetTargetActor(res);
			resFound = true;
			break;
		}
	}

	return resFound;
}

AActor* UBTTask_CollectResources::FindClosestResource(ADecay_of_environmentCharacter* Character, TArray<AActor*> _ResourceActors)
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
