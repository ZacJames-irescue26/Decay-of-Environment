// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Overseerer.generated.h"
USTRUCT(BlueprintType)
struct FStatistics
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 ComponentsValue = 100;
	
	int32 UnitsKilled = 0;
	int32 SpecialUnitsKilled = 0;
	int32 ProtectObjectivesDestroyed = 0;
	int32 ObjectivesReachDestination = 0;
	int32 protectObjectiveGoal = 3;

};
UCLASS()
class DECAY_OF_ENVIRONMENT_API AOverseerer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOverseerer();
	UFUNCTION(NetMulticast, Reliable)
	void Server_SetPlayerOwner(int Player);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	FStatistics statistics;
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

	UPROPERTY(EditAnywhere, Replicated)
	int32 team;
	UPROPERTY(EditAnywhere, Replicated)
	int32 PlayerOwner;
	class ADecay_of_environmentPlayerController* PlayerController;
	


};
