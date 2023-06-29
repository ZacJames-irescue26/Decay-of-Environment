// Fill out your copyright notice in the Description page of Project Settings.


#include "DOEAnimInstance.h"
#include "Decay_of_environment/Decay_of_environmentCharacter.h"
#include "Animation/BlendSpace1D.h"
#include "Animation/AnimSequence.h"

void UDOEAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ADecay_of_environmentCharacter>(TryGetPawnOwner());
	if (Character)
	{
		UnitWalkBlendSpace = Character->UnitWalkBlendSpace;
		UnitIdleAnimSequence = Character->UnitIdleAnimSequence;
	}
}

void UDOEAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Character == nullptr)
	{
		Character = Cast<ADecay_of_environmentCharacter>(TryGetPawnOwner());
	}
	if (Character == nullptr) return;
	//if (Character && UnitIdleAnimSequence == nullptr)
	//{
	//	UnitIdleAnimSequence = Character->UnitIdleAnimSequence;
	//}
	//if (Character && UnitWalkBlendSpace == nullptr)
	//{
	//	UnitWalkBlendSpace = Character->UnitWalkBlendSpace;
	//}
	//if (UnitWalkBlendSpace == nullptr) return;
	//if (UnitIdleAnimSequence == nullptr) return;

	FVector Velocity = Character->GetVelocity();
	Velocity.Z = 0.0f;
	Speed = Velocity.Size();

}
