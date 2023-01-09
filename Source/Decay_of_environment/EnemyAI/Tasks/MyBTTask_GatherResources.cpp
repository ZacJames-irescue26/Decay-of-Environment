// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_GatherResources.h"

UMyBTTask_GatherResources::UMyBTTask_GatherResources()
{

}

EBTNodeResult::Type UMyBTTask_GatherResources::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}

FString UMyBTTask_GatherResources::GetStaticDescription() const
{
	return FString::Printf(TEXT("Gather Resources"));
}
