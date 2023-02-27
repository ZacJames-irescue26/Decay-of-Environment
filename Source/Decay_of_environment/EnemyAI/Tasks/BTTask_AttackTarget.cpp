// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackTarget.h"
#include "../EnemyAIController.h"
#include "../../Decay_of_environmentCharacter.h"
#include "../../DamagableInterface.h"

UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	NodeName = TEXT("Attack Target");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	if (Character->canPerformActions)
	{
		Character->canPerformActions = false;
		if (MyController->GetTargetActor()->IsA(ADecay_of_environmentCharacter::StaticClass()))
		{
			IDamagableInterface* Damagable = Cast<IDamagableInterface>(MyController->GetTargetActor());
			ADecay_of_environmentCharacter* TargetCharacter = Cast<ADecay_of_environmentCharacter>(MyController->GetTargetActor());

			if (Damagable == nullptr) return EBTNodeResult::Failed;
			Damagable->TakeDamage(Character->stats.AttackDamage);
			if (TargetCharacter->stats.currentHealth <= 0)
			{
				MyController->targetActor = nullptr;
			}
		}
		GetWorld()->GetTimerManager().SetTimer(Character->ActionRate, this, &UBTTask_AttackTarget::CanPerformActions, Character->actionDelay);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UBTTask_AttackTarget::CanPerformActions()
{
	Character->canPerformActions = true;
}