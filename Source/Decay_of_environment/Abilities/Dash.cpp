// Fill out your copyright notice in the Description page of Project Settings.


#include "Dash.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ADash::ADash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADash::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	PlayerController = Cast<ADecay_of_environmentPlayerController>(World->GetFirstPlayerController());
}

// Called every frame
void ADash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Parent != nullptr)
	{	
		if (!ensure(PlayerController != nullptr)) return;
		FVector Difference;
		Difference = PlayerController->MousePos - Parent->GetActorLocation();

		FVector Normal = Difference.GetSafeNormal();
		FRotator Rot = Normal.Rotation();
		//FRotator Rot = UKismetMathLibrary::FindLookAtRotation(Parent->GetActorLocation(), PlayerController->MousePos);

		FRotator _rotation;
		_rotation.Yaw = Rot.Yaw;
		SetActorRotation(_rotation);
		SetActorLocation(Parent->GetActorLocation());
		
	}

}

void ADash::SetParentActor(ADecay_of_environmentCharacter* _Parent)
{
	Parent = _Parent;
}
void ADash::DestroyDash()
{
	Destroy(true);
}

