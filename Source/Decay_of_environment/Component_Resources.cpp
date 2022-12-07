// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Resources.h"

AComponent_Resources::AComponent_Resources()
{
	stats.resourceType = EResourceType::Components;
}

void AComponent_Resources::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (stats.amount == 0)
	{
		Destroy();
	}
}
