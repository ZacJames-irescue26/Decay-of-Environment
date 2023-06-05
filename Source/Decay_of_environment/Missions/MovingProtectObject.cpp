// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingProtectObject.h"
#include "Decay_of_environment/Missions/ProtectObjectiveAI.h"
// Sets default values
AMovingProtectObject::AMovingProtectObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	stats.unitID = EUnitClass::ProtectObjective;
	stats.owner = 100;
	stats.team = 0;
	stats.AttackDamage = 0;
	stats.AttackRange = 0;
}

// Called when the game starts or when spawned
void AMovingProtectObject::BeginPlay()
{
	Super::BeginPlay();
	Waypoints.Add({-3160.000000, 190.000000, -130.000000});
	Waypoints.Add({-2130.000000, 2990.000000, -130.000000});
	Waypoints.Add({-820.000000, -100.000000, -130.000000});

}

// Called every frame
void AMovingProtectObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CloseActors.Empty();
	GetOverlappingActors(CloseActors, ADecay_of_environmentCharacter::StaticClass());
	for (auto& Unit : CloseActors)
	{
		ADecay_of_environmentCharacter* character = Cast<ADecay_of_environmentCharacter>(Unit);
		if (character->stats.team == this->stats.team || CloseActors.Num() == 0)
		{
			con = con == nullptr ? Cast<AProtectObjectiveAI>(this->GetController()) : con;

			if (con && WaypointCounter < Waypoints.Num())
			{
				
				con->MoveToLocation(Waypoints[WaypointCounter]);
				if (FMath::Abs(FVector::Distance(GetActorLocation(), Waypoints[WaypointCounter])) <= 500.0f)
				{
					WaypointCounter++;
				}
				return;
			}
		}
		else
		{
			con = con == nullptr ? Cast<AProtectObjectiveAI>(this->GetController()) : con;

			if (con)
			{

				con->StopMovement();
			}
		}

	}
	 
	con = con == nullptr ? Cast<AProtectObjectiveAI>(this->GetController()) : con;
	if (con)
	{

		con->StopMovement();
	}

}

