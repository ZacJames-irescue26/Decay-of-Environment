// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI.h"
#include "TeamInterface.h"
#include <Kismet/GameplayStatics.h>
#include "StorageInterface.h"
#include "DamagableInterface.h"
#include "ResourceInterface.h"
#include <AIController.h>
#include "Components/BoxComponent.h"

#define MIN(a,b)(a<b)?(a):(b)
#define MAX(a,b)(a>b)?(a):(b)

ABaseAI::ABaseAI()
{
	canPerformActions = true;
	actionDelay = 0.5f;
	selectionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("selectionArea"));
	selectionArea->SetBoxExtent(FVector(1500, 1500, 1000));
}

void ABaseAI::SetTargetActor(AActor* val)
{
	previousTarget = targetActor;
	targetActor = val;

	if (targetActor != nullptr) {
		targetActor->GetActorBounds(true, bbLocation, bbExtent);
	}
}

void ABaseAI::MoveAI(FVector loc)
{
	targetActor = nullptr;
	MoveToLocation(loc);
	/*MoveToLocation(const FVector & Dest, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bProjectDestinationToNavigation,
	bool bCanStrafe, TSubclassOf<UNavigationQueryFilter> FilterClass, bool bAllowPartialPaths)*/
	currentAction = EActionType::Move;
}

void ABaseAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	InPawn->GetActorBounds(true, characterBBLocation, characterBBExtent);
}


void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (canPerformActions && GetTargetActor() != nullptr) {
		int32 minDistance = bbExtent.GetAbsMax() + characterBBExtent.GetAbsMax();
		float dist = FVector::Distance(GetCharacter()->GetActorLocation(), targetActor->GetActorLocation());

		if (dist < (minDistance * 1.4)) {
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
				break;
			case EActionType::End:
				break;
			default:
				break;
			}

			GetWorld()->GetTimerManager().SetTimer(ActionRate, this, &ABaseAI::CanPerformActions, actionDelay);
		}
		else {
			MoveToActor(GetTargetActor());
		}
	}
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

void ABaseAI::DepositeResource() {
	if (!GetTargetActor()->Implements<UStorageInterface>()) {
		TArray<AActor*> storageActors;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UStorageInterface::StaticClass(), storageActors);

		for (AActor* store : storageActors) {
			ITeamInterface* team = Cast<ITeamInterface>(store);
			if (team->GetPlayerOwner() == GetRTSCharacter()->GetPlayerOwner()) {
				SetTargetActor(store);
			}
		}
	}
	else {
		IStorageInterface* storage = Cast<IStorageInterface>(GetTargetActor());

		for (FItem& item : GetRTSCharacter()->GetStats().inventory.items) {
			storage->AddItem(item.itemName, item.amount);
		}

		GetRTSCharacter()->GetStats().inventory.items.Empty();

		if (previousTarget->Implements<UResourceInterface>()) {
			SetTargetActor(previousTarget);
			currentAction = EActionType::Gather;
		}
	}
}

void ABaseAI::DamageTarget()
{
	IDamagableInterface* di = Cast<IDamagableInterface>(GetTargetActor());
	if (di->GetHealth() > 0)
	{
		di->TakeDamage(1);
	}
	else if (GetTargetActor()->Implements<UResourceInterface>())
	{
		currentAction = EActionType::Gather;
	}
}


void ABaseAI::AttackTarget(IDamagableInterface* target)
{
	if (target->GetHealth() > 0)
	{
		currentAction = EActionType::Attack;
		SetTargetActor(Cast<AActor>(target));
		MoveToActor(GetTargetActor());
	}
}

void ABaseAI::GatherResource(IResourceInterface* resource)
{
	if (resource->GetAmount() > 0)
	{
		currentAction = EActionType::Gather;
		SetTargetActor(Cast<AActor>(resource));
		MoveToActor(GetTargetActor());
	}
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