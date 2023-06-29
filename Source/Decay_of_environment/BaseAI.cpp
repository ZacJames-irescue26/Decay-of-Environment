// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI.h"
#include "TeamInterface.h"
#include <Kismet/GameplayStatics.h>
#include "StorageInterface.h"
#include "DamagableInterface.h"
#include "ResourceInterface.h"
#include <AIController.h>
#include "Components/BoxComponent.h"
#include "AI/A_star_AIController.h"
#include "Decay_of_environmentPlayerController.h"
#include "UnbuiltBuilding.h"
#include "Misc/App.h"

#define MIN(a,b)(a<b)?(a):(b)
#define MAX(a,b)(a>b)?(a):(b)

ABaseAI::ABaseAI()
{
	canPerformActions = true;
	actionDelay = 0.5f;
	MoveDelay = 1.0f;
	selectionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("selectionArea"));
	selectionArea->SetBoxExtent(FVector(1500, 1500, 1000));
	i = 0;
	bReplicates = true;
}


void ABaseAI::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseAI, previousTarget);
	DOREPLIFETIME(ABaseAI, targetActor);
	DOREPLIFETIME(ABaseAI, currentAction);


}

void ABaseAI::SetTargetActor_Implementation(AActor* val)
{
	previousTarget = targetActor;
	targetActor = val;
	if (targetActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Actor is nullptr"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Actor modified: %s"), *targetActor->GetName());

	}
	if (targetActor != nullptr) {
		targetActor->GetActorBounds(true, bbLocation, bbExtent);
	}
	
	ServerSetTargetActor(val);
	ClientSetTargetActor(val);
}


void ABaseAI::ServerSetTargetActor_Implementation(AActor* val)
{
	targetActor = val;
}


void ABaseAI::ClientSetTargetActor_Implementation(AActor* val)
{
	targetActor = val;
}

void ABaseAI::MoveAI_Implementation(FVector loc, AActor* a)
{
	targetActor = nullptr;
	ReachedDestination = false;
	ADecay_of_environmentCharacter* Agent = GetPawn<ADecay_of_environmentCharacter>();
	if (Agent)
	{
		Agent->Velocity = FVector::ZeroVector;
	}
	Destination = loc;
	currentAction = EActionType::Move;
	
	///*MoveToLocation(const FVector & Dest, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bProjectDestinationToNavigation,
	//bool bCanStrafe, TSubclassOf<UNavigationQueryFilter> FilterClass, bool bAllowPartialPaths)*/
}
void ABaseAI::CanMove()
{
	Canmove = true;
}
void ABaseAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	InPawn->GetActorBounds(true, characterBBLocation, characterBBExtent);
}


FVector ABaseAI::Seek(ADecay_of_environmentCharacter* Agent)
{
	if (GetTargetActor() != nullptr)
	{
		FVector desired = GetTargetActor()->GetActorLocation() - Agent->GetActorLocation();
		desired = desired * (Agent->MaxSpeed/ desired.Size());
		FVector force = desired - Agent->Velocity;
		return force * (Agent->MaxForce / Agent->MaxSpeed);
	}
	return FVector::ZeroVector;
}
FVector ABaseAI::SeekOnLocation(FVector Location)
{
	ADecay_of_environmentCharacter* Agent = GetPawn<ADecay_of_environmentCharacter>();
	if (Agent)
	{
		FVector desired = Location - Agent->GetActorLocation();
		desired = desired * (Agent->MaxSpeed / desired.Size());
		FVector force = desired - Agent->Velocity;
		return force * (Agent->MaxForce / Agent->MaxSpeed);
	}
	return FVector::ZeroVector;
}

void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AIbehaviour(DeltaTime);
	if (!ReachedDestination)
	{
		ADecay_of_environmentCharacter* pawn = GetPawn<ADecay_of_environmentCharacter>();
		if (pawn)
		{
			FVector seek = SeekOnLocation(Destination);
			pawn->Velocity += seek * DeltaTime;
			float _Speed = pawn->Velocity.Size();
			if (_Speed > pawn->MaxSpeed)
			{
				pawn->Velocity = pawn->Velocity * (4.0f / Speed);
			}
			FVector CurrentPos = pawn->GetActorLocation();

			pawn->SetActorLocation(CurrentPos + (pawn->Velocity * DeltaTime));
		}
		else if ((pawn->GetActorLocation() - Destination).Size() <= 10.0f)
		{
			ReachedDestination = true;
		}
		else
		{
			ReachedDestination = true;
		}
	}
	

}

void ABaseAI::AIbehaviour_Implementation(float DeltaTime)
{
	if (currentAction == EActionType::patrol)
	{
		AttackMove();
	}
	if (canPerformActions && targetActor != nullptr) {
		int32 minDistance = bbExtent.GetAbsMax() + characterBBExtent.GetAbsMax();
		float dist = FVector::Distance(GetCharacter()->GetActorLocation(), targetActor->GetActorLocation());
		ADecay_of_environmentCharacter* _Character = Cast<ADecay_of_environmentCharacter>(GetCharacter());

		//if (dist < (minDistance * _Character->stats.AttackRange)) 
		if (dist < (_Character->stats.AttackRange))
		{
			canPerformActions = false;
			StopMovement();

			switch (currentAction) {
			case EActionType::Attack:
				DamageTarget();
				break;
			case EActionType::Gather:
				Gather();
				break;
			case EActionType::DepositeResources:
				DepositeResource();
				break;
			case EActionType::Build:
				BuildBuilding();
				break;
			case EActionType::End:
				break;
			default:
				break;
			}

			GetWorld()->GetTimerManager().SetTimer(ActionRate, this, &ABaseAI::CanPerformActions, actionDelay);
		}
		else {
			//MoveToActor(GetTargetActor());
			if (targetActor)
			{
				ADecay_of_environmentCharacter* pawn = GetPawn<ADecay_of_environmentCharacter>();
				if (pawn)
				{
					FVector seek = Seek(GetPawn<ADecay_of_environmentCharacter>());
					pawn->Velocity += seek * DeltaTime;
					float _Speed = pawn->Velocity.Size();
					if (_Speed > pawn->MaxSpeed)
					{
						pawn->Velocity = pawn->Velocity * (4.0f/Speed);
					}
					FVector CurrentPos = pawn->GetActorLocation();

					pawn->SetActorLocation(CurrentPos + (pawn->Velocity * DeltaTime));
				}
			}
		}
	}
}



void ABaseAI::BeginPlay()
{
	Super::BeginPlay();
	GridManager = Cast<ACubeGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACubeGridManager::StaticClass()));
}

void ABaseAI::Gather() {
	IResourceInterface* ri = Cast<IResourceInterface>(GetTargetActor());
	int32 amount = ri->GetAmount();
	int32 space = GetRTSCharacter()->GetCarryWeight() - GetRTSCharacter()->GetWeight();

	// Does the target have resources left
	if (amount > 0) {
		// Do we have carry space left
		if (space > 0) {
			// Find the lowest amount to gather, either the resources has less than we can carry / gather or we lack the space to gather fully
			int32 amountToTake = MIN(amount, space);
			amountToTake = MIN(GetRTSCharacter()->GetGatherAmount(), amountToTake);

			ri->TakeResources(amountToTake);
			GetRTSCharacter()->RecieveResources(amountToTake, ri);
		}
		// We ran out of space so return to storage
		else {
			currentAction = EActionType::DepositeResources;
		}
	}
	// The target ran out of resources, but we still have carry space
	else if (space > 0) {
		TArray<AActor*> resourceActors;

		GetNearbyActors(resourceActors);
		//ShuffleArray<AActor*>(resourceActors);

		bool resFound = FindResource(ri->GetType(), resourceActors);

		if (resourceActors.Num() == 0 || !resFound) {
			currentAction = EActionType::DepositeResources;
		}
	}
	// We ran out of space so return to storage
	else {
		currentAction = EActionType::DepositeResources;
	}
}

bool ABaseAI::FindResource(EResourceType resType, TArray<AActor*> actors) {
	bool resFound = false;

	for (AActor* res : actors) {
		IResourceInterface* resi = Cast<IResourceInterface>(res);

		if (resi != NULL && resi->GetType() == resType && resi->GetAmount() > 0 && !res->IsUnreachable()) {
			// Is this resource that can be attacked?
			if (res->Implements<UDamagableInterface>()) {
				IDamagableInterface* damagei = Cast<IDamagableInterface>(res);

				// Does the target have health left?
				if (damagei->GetHealth() > 0) {
					// Attack the target
					SetTargetActor(res);
					resFound = true;
					currentAction = EActionType::Attack;
					break;
				}
				// They're dead, so gather from it
				else {
					SetTargetActor(res);
					resFound = true;
					break;
				}
			}
			// They can't be attacked, so gather from it
			else {
				SetTargetActor(res);
				resFound = true;
				break;
			}
		}
	}

	return resFound;
}

void ABaseAI::DepositeResource() 
{
	if (!GetTargetActor()->Implements<UStorageInterface>()) 
	{
		TArray<AActor*> storageActors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UStorageInterface::StaticClass(), storageActors);
		

		for (AActor* store : storageActors) 
		{
			ITeamInterface* team = Cast<ITeamInterface>(store);
			if (team->GetPlayerOwner() == GetRTSCharacter()->GetPlayerOwner()) 
			{
				//TODO: Find the closest base
				SetTargetActor(store);
				break;
			}
		}
	}
	else 
	{
		IStorageInterface* storage = Cast<IStorageInterface>(GetTargetActor());

		for (FItem& item : GetRTSCharacter()->GetStats().inventory.items) 
		{
			storage->AddItem(item.itemName, item.amount);
			ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(GetWorld()->GetFirstPlayerController());
			PlayerController->GetOverseerer()->statistics.ComponentsValue += item.amount;

		}

		GetRTSCharacter()->GetStats().inventory.items.Empty();
		
		if (previousTarget->Implements<UResourceInterface>()) 
		{
			SetTargetActor(previousTarget);
			currentAction = EActionType::Gather;
		}
	}
}

void ABaseAI::DamageTarget_Implementation()
{
	StopMovement();
	IDamagableInterface* di = Cast<IDamagableInterface>(GetTargetActor());
	if (di->GetHealth() > 0)
	{
		ADecay_of_environmentCharacter* _character = GetRTSCharacter();
		di->TakeDamage(_character->stats.AttackDamage);
	}
	else if (GetTargetActor()->Implements<UResourceInterface>())
	{
		currentAction = EActionType::Gather;
	}
}


void ABaseAI::AttackTarget_Implementation(AActor* target)
{
		currentAction = EActionType::Attack;
		SetTargetActor(target);
		MoveToActor(GetTargetActor());
		UE_LOG(LogTemp, Warning, TEXT("Attacking target %s"), *GetTargetActor()->GetName());
		return;
}

void ABaseAI::GatherResource(AActor* resource)
{
		currentAction = EActionType::Gather;
		SetTargetActor(Cast<AActor>(resource));
		MoveToActor(GetTargetActor());
		return;
}


ADecay_of_environmentCharacter* ABaseAI::GetRTSCharacter()
{
	if (rtsCharacter == nullptr)
	{
		rtsCharacter = Cast<ADecay_of_environmentCharacter>(GetCharacter());
	}
	return rtsCharacter;
	
}

void ABaseAI::CanPerformActions()
{
	canPerformActions = true;
}

void ABaseAI::GetNearbyActors(TArray<AActor*>& actors) {
	selectionArea->SetWorldLocation(GetRTSCharacter()->GetActorLocation());
	selectionArea->GetOverlappingActors(actors);
}

void ABaseAI::Patrol(FVector Location, AActor* c)
{
	
	currentAction = EActionType::patrol;
	//UE_LOG(LogTemp, Warning, TEXT("Current Action: %i"), currentAction);
	MoveToLocation(Location, 10.0f);

}
void ABaseAI::AttackMove()
{
	TArray<AActor*> NearActors;
	GetRTSCharacter()->GetOverlappingActors(NearActors, ADecay_of_environmentCharacter::StaticClass());
	//UE_LOG(LogTemp, Warning, TEXT("Actors in range %i"), NearActors.Num());
	if (NearActors.Num() > 0)
	{
		for (AActor* Near : NearActors)
		{
			ADecay_of_environmentCharacter* _Character = Cast<ADecay_of_environmentCharacter>(Near);
			if(!_Character) return;
			if (_Character->stats.owner != GetRTSCharacter()->GetPlayerOwner() && _Character->stats.team != GetRTSCharacter()->GetPlayerTeam())
			{
				SetTargetActor(_Character);
				currentAction = EActionType::Attack;
			}
		}
	}
}

void ABaseAI::Build_Implementation(AUnbuiltBuilding* _Building)
{
	SetTargetActor(_Building);
	currentAction = EActionType::Build;
}

void ABaseAI::BuildBuilding_Implementation()
{
	AUnbuiltBuilding* _Building = Cast<AUnbuiltBuilding>(GetTargetActor());
	_Building->StartTimer();
	

}

