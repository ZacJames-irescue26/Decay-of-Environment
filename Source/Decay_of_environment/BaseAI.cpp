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
}

void ABaseAI::SetTargetActor(AActor* val)
{
	previousTarget = targetActor;
	targetActor = val;

	if (targetActor != nullptr) {
		targetActor->GetActorBounds(true, bbLocation, bbExtent);
	}
}

//void ABaseAI::MoveAI(FVector loc, AActor* a)
//{
//	targetActor = nullptr;
//	MoveToLocation(loc);
//	///*MoveToLocation(const FVector & Dest, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bProjectDestinationToNavigation,
//	//bool bCanStrafe, TSubclassOf<UNavigationQueryFilter> FilterClass, bool bAllowPartialPaths)*/
//	currentAction = EActionType::Move;
//	
//	//int XPos = a->GetActorLocation().X/GridManager->TileHorizontalOffset;
//	//int YPos = a->GetActorLocation().Y/GridManager->TileVerticalOffset;
//	//int FinalXPos = loc.X / GridManager->TileHorizontalOffset;
//	//int FinalYPos = loc.Y / GridManager->TileVerticalOffset;
//	//if (XPos > 0 && YPos > 0 && FinalXPos > 0 && FinalYPos > 0)
//	//{
//	//	Path = AA_star_AIController::A_star(GridManager->CubeGrid[XPos][YPos], GridManager->CubeGrid[FinalXPos][FinalYPos], GridManager->TileHorizontalOffset, GridManager->TileVerticalOffset, GridManager->GridWidth, GridManager->GridHeight, GridManager->CubeGrid);
//	//}
//	//Actor = a;
//	//ACubeTile* start, ACubeTile* end, float TileHorizontalOffset, float TileVerticalOffset, int32 MapXSize, int32 MapYSize, TArray<TArray<ACubeTile*>> AllMap 
//	//Canmove = true;
//	//int i = 0;
//	//while(i < Path.Num())
//	//{
//	//	UE_LOG(LogTemp, Warning, TEXT("CanMove: %i, Timer"), Canmove);
//	//	//Canmove = false;
//	//	for (float j = 0; j < 1; j = j + 0.1)
//	//	{
//	//		a->SetActorLocation(FMath::Lerp(a->GetActorLocation(), Path[i]->GetActorLocation(),j));
//	//		//a->SetActorLocation(Path[i]->GetActorLocation());
//	//		UE_LOG(LogTemp, Warning, TEXT("CanMove: %i"), Canmove);
//	//		
//
//	//	}
//	//	i++;
//	//}
//
//
//
//}
void ABaseAI::MoveAI_Implementation(FVector loc, AActor* a)
{
	targetActor = nullptr;
	MoveToLocation(loc,10.0f);
	
	///*MoveToLocation(const FVector & Dest, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bProjectDestinationToNavigation,
	//bool bCanStrafe, TSubclassOf<UNavigationQueryFilter> FilterClass, bool bAllowPartialPaths)*/
	currentAction = EActionType::Move;
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


void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (currentAction == EActionType::patrol)
	{
		AttackMove();
	}
	if (canPerformActions && GetTargetActor() != nullptr) {
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
	//if (Actor != nullptr)
	//{
	//	//float JourneyLength = (Path[i]->GetActorLocation() - Actor->GetActorLocation()).Size();
	//	FVector Location = Actor->GetActorLocation();
	//	if (i < Path.Num())
	//	{
	//		FVector Direction = (Path[Path.Num() - 1 - i]->GetActorLocation() - Actor->GetActorLocation()).GetSafeNormal();
	//		Location += Speed * DeltaTime * Direction;
	//		Actor->SetActorLocation(Location);
	//		if (Actor->GetActorLocation().X > Path[Path.Num() - 1 - i]->GetActorLocation().X -10 && Actor->GetActorLocation().X < Path[Path.Num() - 1 - i]->GetActorLocation().X + 10 
	//			&& Actor->GetActorLocation().Y  > Path[Path.Num() - 1 - i]->GetActorLocation().Y - 10 && Actor->GetActorLocation().Y < Path[Path.Num() - 1 - i]->GetActorLocation().Y + 10  && i < Path.Num())
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("Added to i: %i"), i);
	//			i++;
	//		}
	//	}
	//	else if(i >= Path.Num())
	//	{
	//		i = 0;
	//	}

	//}
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
			PlayerController->GetOverseerer()->ComponentsValue += item.amount;

		}

		GetRTSCharacter()->GetStats().inventory.items.Empty();
		
		if (previousTarget->Implements<UResourceInterface>()) 
		{
			SetTargetActor(previousTarget);
			currentAction = EActionType::Gather;
		}
	}
}

void ABaseAI::DamageTarget()
{
	StopMovement();
	IDamagableInterface* di = Cast<IDamagableInterface>(GetTargetActor());
	if (di->GetHealth() > 0)
	{
		di->TakeDamage(GetRTSCharacter()->stats.AttackDamage);
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