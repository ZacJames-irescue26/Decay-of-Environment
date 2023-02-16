// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackTarget.h"
#include "../EnemyAIController.h"
#include "../../Decay_of_environmentCharacter.h"
#include "../../DamagableInterface.h"

UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	NodeName = TEXT("Attack Target");
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	APawn* AIPawn{ MyController->GetPawn() };
	ADecay_of_environmentCharacter* Character = Cast<ADecay_of_environmentCharacter>(AIPawn);
	if (MyController->GetTargetActor()->IsA(ADecay_of_environmentCharacter::StaticClass()))
	{
		IDamagableInterface* Damagable = Cast<IDamagableInterface>(MyController->GetTargetActor());
		if (Damagable == nullptr) return EBTNodeResult::Failed;
		Damagable->TakeDamage(Character->stats.AttackDamage);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
