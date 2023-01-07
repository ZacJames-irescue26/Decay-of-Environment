// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpawnUnit.h"

UBTTask_SpawnUnit::UBTTask_SpawnUnit()
{

}

EBTNodeResult::Type UBTTask_SpawnUnit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//if()
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SpawnUnit::GetStaticDescription() const
{
	return FString::Printf(TEXT("Unit"));
}
