// Copyright Epic Games, Inc. All Rights Reserved.

#include "Decay_of_environmentPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Decay_of_environmentCharacter.h"
#include "Engine/World.h"
#include <DrawDebugHelpers.h>
#include "Enums_Structs.h"
#include "BaseAI.h"
#include "DamagableInterface.h"
#include "ResourceInterface.h"
#include "UI/UserInterface.h"

ADecay_of_environmentPlayerController::ADecay_of_environmentPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	selectionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("selectionArea"));
	selectionArea->SetBoxExtent(FVector(0, 0, 400));
	static ConstructorHelpers::FClassFinder<UUserWidget> UserInterfaceBPClass(TEXT("/Game/TopDown/Blueprints/BP_UserInterface"));
	if (!ensure(UserInterfaceBPClass.Class != nullptr)) return;

	UserInterfaceClass = UserInterfaceBPClass.Class;
}

void ADecay_of_environmentPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	MousePos = hit.Location;



	GetHitResultUnderCursor(ECC_Visibility, true, hit);
	if(leftMouseDown)
	{
		mouseEnd = hit.Location;
		FollowTime += DeltaTime;


		FollowTime = 0.f;
		centerMouseLocation = FVector((mouseStart+mouseEnd)/2);
		dist = FVector::Dist(mouseEnd, mouseStart) / 2;
		selectionSize = FVector(dist,dist,100);

		DrawDebugBox(GetWorld(), centerMouseLocation, selectionSize, FQuat(0,0,0,0), FColor::Black);

	}
}

void ADecay_of_environmentPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Adding player"));
	if (!ensure(UserInterfaceClass != nullptr)) return;
	UserInterface = CreateWidget<UUserInterface>(this, UserInterfaceClass);
	if (!ensure(UserInterface != nullptr)) return;

	UserInterface->Setup();

}

void ADecay_of_environmentPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ADecay_of_environmentPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ADecay_of_environmentPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("RightClick", IE_Pressed, this, &ADecay_of_environmentPlayerController::RightClick);
	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADecay_of_environmentPlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &ADecay_of_environmentPlayerController::OnTouchReleased);

}

void ADecay_of_environmentPlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	leftMouseDown = true;
	mouseStart = hit.Location;
	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}

void ADecay_of_environmentPlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	leftMouseDown = false;
	SelectUnits();
}

void ADecay_of_environmentPlayerController::OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = true;
	OnSetDestinationPressed();
}

void ADecay_of_environmentPlayerController::OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ADecay_of_environmentPlayerController::AttackTarget(IDamagableInterface* target)
{
	if (selectedUnits.Num() > 0)
	{
		for (AActor* a : selectedUnits)
		{
			if (a->IsA(ADecay_of_environmentCharacter::StaticClass()))
			{
				ADecay_of_environmentCharacter* c = Cast<ADecay_of_environmentCharacter>(a);
				if (c->GetPlayerOwner() != -1) {
					ABaseAI* con = Cast<ABaseAI>(c->GetController());
					con->AttackTarget(target);
				}
			}

		}
	}
}

void ADecay_of_environmentPlayerController::GatherResources(IResourceInterface* res)
{
	if (selectedUnits.Num() > 0)
	{
		for (AActor* a : selectedUnits)
		{
			if (a->IsA(ADecay_of_environmentCharacter::StaticClass()))
			{
				ADecay_of_environmentCharacter* c = Cast<ADecay_of_environmentCharacter>(a);
				ABaseAI* con = Cast<ABaseAI>(c->GetController());
				con->GatherResource(res);
			}
		}
	}

}


void ADecay_of_environmentPlayerController::RightClick()
{
	//FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, hit);
	if (hit.bBlockingHit)
	{

		AActor* targetFound = hit.GetActor();


		bool isdamagable = targetFound->Implements<UDamagableInterface>();
		bool isResource = targetFound->Implements<UResourceInterface>();
		if (isdamagable)
		{

			IDamagableInterface* damagable = GetDamagable(targetFound);

			if (damagable->GetHealth() > 0)
			{
				ITeamInterface* team = GetTeam(targetFound);
				int32 targetTeam = team->GetPlayerTeam();
				int32 overseererTeam = GetOverseerer()->GetTeam();
				if (team->GetPlayerOwner() == -1 || targetTeam != overseererTeam)
				{
					AttackTarget(damagable);
				}

			}
			else if (isResource)
			{
				IResourceInterface* res = GetResource(targetFound);
				GatherResources(res);
			}
		}
		else if (isResource)
		{
			IResourceInterface* res = GetResource(targetFound);
			GatherResources(res);
			//res->TakeResources(10);
		}
		else
		{
			MoveUnits(hit.Location);
		}

	}
}

void ADecay_of_environmentPlayerController::SelectUnits()
{
	selectionArea->SetWorldLocation(mouseEnd);
	selectionArea->SetBoxExtent(selectionSize);
	TArray<AActor*> actors;
	selectionArea->GetOverlappingActors(actors);
	if (actors.Num() > 0)
	{
		for (AActor* a : actors)
		{
			if (a->IsA(ADecay_of_environmentCharacter::StaticClass()))
			{
				ADecay_of_environmentCharacter* character = Cast<ADecay_of_environmentCharacter>(a);
				if (character->GetType() != ECharacterType::Animal)
				{
					selectedUnits.Add(a);
				}
			}
		}
	}

}

void ADecay_of_environmentPlayerController::MoveUnits(FVector loc)
{
	if (selectedUnits.Num() > 0) {
		for (AActor* a : selectedUnits) {
			if (a->IsA(ADecay_of_environmentCharacter::StaticClass())) {
				ADecay_of_environmentCharacter* c = Cast<ADecay_of_environmentCharacter>(a);

				if (c->GetPlayerOwner() != -1) {
					ABaseAI* con = Cast<ABaseAI>(c->GetController());
					con->MoveAI(loc);
				}
			}
		}
	}
}


IDamagableInterface* ADecay_of_environmentPlayerController::GetDamagable(AActor* other)
{
	return Cast<IDamagableInterface>(other);
}
IResourceInterface* ADecay_of_environmentPlayerController::GetResource(AActor* other)
{
	return Cast<IResourceInterface>(other);
}
ITeamInterface* ADecay_of_environmentPlayerController::GetTeam(AActor* other)
{
	return Cast<ITeamInterface>(other);
}



AOverseerer* ADecay_of_environmentPlayerController::GetOverseerer()
{
	if (overseerer == NULL)
	{
		overseerer = Cast<AOverseerer>(GetPawn());
	}
	return overseerer;
}


