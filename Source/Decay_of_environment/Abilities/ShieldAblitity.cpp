// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldAblitity.h"

// Sets default values
AShieldAblitity::AShieldAblitity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShieldLifeTime = 3.0f;
}

// Called when the game starts or when spawned
void AShieldAblitity::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(ShieldTimerHandle, this, &AShieldAblitity::DestroyShield, ShieldLifeTime);
}

// Called every frame
void AShieldAblitity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Parent != nullptr)
	{
		SetActorLocation(Parent->GetActorLocation());
	}
}

void AShieldAblitity::SetParentActor(ADecay_of_environmentCharacter* _Parent)
{
		Parent = _Parent; 
}
void AShieldAblitity::DestroyShield()
{
	Destroy(true);
}


