// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Overseerer.generated.h"

UCLASS()
class DECAY_OF_ENVIRONMENT_API AOverseerer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOverseerer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	int32 GetTeam() const { return team; }
	void SetTeam(int32 val) { team = val; }
	int32 GetPlayerOwner() const { return PlayerOwner; }
	void SetPlayerOwner(int32 val) { PlayerOwner = val; }
	UPROPERTY(EditAnywhere)
	int32 team;
	UPROPERTY(EditAnywhere)
	int32 PlayerOwner;
	//TODO setup player owner on spawn
	UPROPERTY(EditAnywhere)
	int32 ComponentsValue = 0;

};
