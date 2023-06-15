// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeTile.h"
#include <Components/SceneComponent.h>


// Sets default values
ACubeTile::ACubeTile()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetupAttachment(RootComponent);
	
	

}


