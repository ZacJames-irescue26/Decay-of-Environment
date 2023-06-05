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
	MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	//MyController->MoveToLocation(FVector(380.0, -150.0, 110.0));
	//IResourceInterface* ri = Cast<IResourceInterface>(GetTargetActor());
	int32 amount;
	
	
	
	if (MyController->canPerformActions)
	{
		MyController->canPerformActions = false;
		if (MyController->GetTargetActor() != nullptr)
		{
			IResourceInterface* ri = Cast<IResourceInterface>(MyController->GetTargetActor());
			if (ri != nullptr)
			{

				int32 space = MyController->GetRTSCharacter()->GetCarryWeight() - MyController->GetRTSCharacter()->GetWeight(); 
				amount = ri->GetAmount();
				if (amount > 0)
				{
					// Do we have carry space left
					if (space > 0)
					{

						// Find the lowest amount to gather, either the resources has less than we can carry / gather or we lack the space to gather fully
						int32 amountToTake = MIN(amount, space);
						amountToTake = MIN(MyController->GetRTSCharacter()->GetGatherAmount(), amountToTake);

						ri->TakeResources(amountToTake);
						MyController->GetRTSCharacter()->RecieveResources(amountToTake, ri);
					}
					// We ran out of space so return to storage
					else {
						GetWorld()->GetTimerManager().SetTimer(Character->ActionRate, this, &UBTTask_CollectResources::CanPerformActions, Character->actionDelay);
						return EBTNodeResult::Succeeded;
					}
				}
				// The target ran out of resources, but we still have carry space
				else if (space > 0) {
					/*TArray<AActor*> resourceActors;

					GetNearbyActors(resourceActors);*/
					//ShuffleArray<AActor*>(resourceActors);

					/*bool resFound = FindResource(ri->GetType(), ResourceActors);*/

					if (ri == nullptr) {
						GetWorld()->GetTimerManager().SetTimer(Character->ActionRate, this, &UBTTask_CollectResources::CanPerformActions, Character->actionDelay);
						return EBTNodeResult::Failed;
					}
				}
				// We ran out of space so return to storage
				else {
					GetWorld()->GetTimerManager().SetTimer(Character->ActionRate, this, &UBTTask_CollectResources::CanPerformActions, Character->actionDelay);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	// Does the target have resources left
	
	return EBTNodeResult::Failed;
}

void UBTTask_CollectResources::CanPerformActions()
{
	MyController->canPerformActions =  true;
}

FString UBTTask_CollectResources::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}


