// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource.h"

// Sets default values
AResource::AResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AResource::TakeResources(int32 amount)
{
	stats.amount -= amount;
}

EResourceType AResource::GetType()
{
	return stats.resourceType;
}

int32 AResource::GetAmount()
{
	return stats.amount;
}



