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

	if (MyController->GetTargetActor() != nullptr)
	{
		MyController->MoveToActor(MyController->GetTargetActor());
		for (FItem& item : MyController->GetRTSCharacter()->GetStats().inventory.items)
		{
			MyController->GameInstance->EnemyComponentValue += item.amount;
		}
		MyController->GetRTSCharacter()->GetStats().inventory.items.Empty();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;

	
}

FString UBTTask_DepositResources::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}



