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
#include "AI/A_star_AIController.h"
#include "TileGrid/CubeTile.h"
#include "UI/TestHUD.h"
#include <Kismet/GameplayStatics.h>
#include "UnbuiltBuilding.h"
#include "BuildingIcon.h"
#include "DOEPlayerState.h"
#include "Net/UnrealNetwork.h"

ADecay_of_environmentPlayerController::ADecay_of_environmentPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	MaxZoom = 4000;
	MinZoom = 500;
	ZoomRate = 100;

	/*selectionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("selectionArea"));
	selectionArea->SetBoxExtent(FVector(0, 0, 400));*/
	/*static ConstructorHelpers::FClassFinder<UUserWidget> UserInterfaceBPClass(TEXT("/Game/TopDown/Blueprints/BP_UserInterface"));
	if (!ensure(UserInterfaceBPClass.Class != nullptr)) return;

	UserInterfaceClass = UserInterfaceBPClass.Class;*/
}


void ADecay_of_environmentPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADecay_of_environmentPlayerController, selectedUnits);
	DOREPLIFETIME(ADecay_of_environmentPlayerController, targetFound);
	DOREPLIFETIME(ADecay_of_environmentPlayerController, overseerer);
	DOREPLIFETIME(ADecay_of_environmentPlayerController, m_Building);



}

void ADecay_of_environmentPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	MousePos = hit.Location;

	FVector2D ViewportSize;
	if (IsLocalController())
	{
		GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
		GetMousePosition(LocationX, LocationY);
		//dont know why its reversed
		if ((LocationX/ViewportSize.X) >= 0.975)
		{
			_Location.Y += 10;
		}
		if ((LocationX / ViewportSize.X) <= 0.025)
		{
			_Location.Y -= 10;
		}
		if ((LocationY / ViewportSize.Y) >= 0.975)
		{
			_Location.X -= 10;
		}
		if ((LocationY / ViewportSize.Y) <= 0.025)
		{
			_Location.X += 10;
		}
		if (overseerer)
		{
			overseerer->SetActorLocation(_Location);
		}
		else
		{
			GetOverseerer();
		}

	}
	
	GetHitResultUnderCursor(ECC_Visibility, true, hit);
	if(leftMouseDown)
	{
		mouseEnd = hit.Location;
		/*FollowTime += DeltaTime;
		GetMousePosition(MouseEndX, MouseEndY);

		FollowTime = 0.f;
		centerMouseLocation = FVector((mouseStart+mouseEnd)/2);
		dist = FVector::Dist(mouseEnd, mouseStart) / 2;
		selectionSize = FVector(dist,dist,1000);

		DrawDebugBox(GetWorld(), centerMouseLocation, selectionSize, FQuat(0,0,0,0), FColor::Black);*/

	}

}
void ADecay_of_environmentPlayerController::Server_UpdatePlayerOwner_Implementation()
{
		if (overseerer == nullptr)
		{
			overseerer = GetOverseerer();
		}
		DOEPlayerState = GetPlayerState<ADOEPlayerState>();
		if (DOEPlayerState && overseerer)
		{
			overseerer->SetPlayerOwner(DOEPlayerState->GetPlayerOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Overseer Is nullptr"))
		}
}
void ADecay_of_environmentPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Server_UpdatePlayerOwner();
	
	/*for (int i = 0; i < UGameplayStatics::GetNumPlayerControllers(GetWorld()); i++)
	{
		auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), i);
		
	}*/
	//UE_LOG(LogTemp, Warning, TEXT("Adding player"));
	//if (!ensure(UserInterfaceClass != nullptr)) return;
	//UserInterface = CreateWidget<UUserInterface>(this, UserInterfaceClass);
	//if (!ensure(UserInterface != nullptr)) return;

	//UserInterface->Setup();
	AbilityManager = Cast<AAbilityManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAbilityManager::StaticClass()));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuilding::StaticClass(), ActorBuildings);
	for (auto& Building : ActorBuildings)
	{
		Buildings.Add(Cast<ABuilding>(Building));
	}
}

void ADecay_of_environmentPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ADecay_of_environmentPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ADecay_of_environmentPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("RightClick", IE_Pressed, this, &ADecay_of_environmentPlayerController::RightClick);
	InputComponent->BindAction("RightClick", IE_Released, this, &ADecay_of_environmentPlayerController::RightClickReleased);

	InputComponent->BindAction("Button1", IE_Pressed, this, &ADecay_of_environmentPlayerController::Button1);
	InputComponent->BindAction("Button2", IE_Pressed, this, &ADecay_of_environmentPlayerController::Button2);

	InputComponent->BindAction("MoveAttack", IE_Pressed, this, &ADecay_of_environmentPlayerController::Moveattack);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ADecay_of_environmentPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ADecay_of_environmentPlayerController::ZoomOut);

	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ADecay_of_environmentPlayerController::ZoomOut);

	InputComponent->BindAction("Number1", IE_Pressed, this, &ADecay_of_environmentPlayerController::ZoomOut);
	InputComponent->BindAction("ShiftNumber1", IE_Pressed, this, &ADecay_of_environmentPlayerController::ZoomOut);
	

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ADecay_of_environmentPlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &ADecay_of_environmentPlayerController::OnTouchReleased);
	
}

void ADecay_of_environmentPlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	leftMouseDown = true;
	mouseStart = hit.Location;
	GetMousePosition(MouseStartX, MouseStartY);
	for (ADecay_of_environmentCharacter* c : selectedUnits)
	{
		c->Decal->SetVisibility(false);
	}
	selectedUnits.Empty();
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


void ADecay_of_environmentPlayerController::Server_AttackTarget_Implementation(AActor* target, ADecay_of_environmentCharacter* c)
{
	ABaseAI* con = Cast<ABaseAI>(c->GetController());
	con->AttackTarget(target);
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
				if (c->GetPlayerOwner() != -1 && target->GetHealth() > 0) {
					AActor* CurrentTarget = Cast<AActor>(target);
					Server_AttackTarget(CurrentTarget,c);
				}
			}

		}
	}
}

void ADecay_of_environmentPlayerController::Moveattack()
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
					con->Patrol(hit.Location, c);
				}
			}

		}
	}
}

void ADecay_of_environmentPlayerController::Server_GatherResources_Implementation(AActor* res, ADecay_of_environmentCharacter* c)
{
	ABaseAI* con = Cast<ABaseAI>(c->GetController());
	con->GatherResource(res);
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
				
				if (res->GetAmount() > 0)
				{
					AActor* TargetResource = Cast<AActor>(res);
					Server_GatherResources(TargetResource,c);
				}
			}
		}
	}
}

void ADecay_of_environmentPlayerController::Build(AUnbuiltBuilding* Building)
{
	if (selectedUnits.Num() > 0)
	{
		for (AActor* a : selectedUnits)
		{
			if (a->IsA(ADecay_of_environmentCharacter::StaticClass()))
			{
				ADecay_of_environmentCharacter* c = Cast<ADecay_of_environmentCharacter>(a);
				ABaseAI* con = Cast<ABaseAI>(c->GetController());
				con->Build(Building);
			}
		}
	}

}


void ADecay_of_environmentPlayerController::RightClick()
{
	//FHitResult TraceHitResult;
	RightMouseDown = true;
	GetHitResultUnderCursor(ECC_Visibility, true, hit);
	if (hit.bBlockingHit)
	{

		targetFound = hit.GetActor();


		bool isdamagable = targetFound->Implements<UDamagableInterface>();
		bool isResource = targetFound->Implements<UResourceInterface>();
		bool isBuilding = targetFound->Implements<UBuidlingInterface>();
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
			if (isBuilding)
			{
				AUnbuiltBuilding* Building = Cast<AUnbuiltBuilding>(targetFound);
				if (Building->GetPlayerOwner() == GetOverseerer()->GetPlayerOwner() && Building->GetPlayerTeam() == GetOverseerer()->GetTeam())
				{
					Build(Building);
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

void ADecay_of_environmentPlayerController::RightClickReleased()
{
	RightMouseDown = false;
}

void ADecay_of_environmentPlayerController::SelectUnits()
{
	//selectionArea->SetWorldLocation(mouseEnd);
	//selectionArea->SetBoxExtent(selectionSize);
	TArray<AActor*> actors;
	for (ADecay_of_environmentCharacter* c : selectedUnits)
	{
		c->Decal->SetVisibility(false);
	}
	selectedUnits.Empty();
	//selectionArea->GetOverlappingActors(actors);
	ATestHUD* HUD = Cast<ATestHUD>(GetHUD());
	actors = HUD->SelectedActors;
	if (actors.Num() > 0)
	{
		for (AActor* a : actors)
		{
			if (a->IsA(ADecay_of_environmentCharacter::StaticClass()))
			{
				ADecay_of_environmentCharacter* character = Cast<ADecay_of_environmentCharacter>(a);
				if (character->GetType() != ECharacterType::Animal)
				{
					if (character->GetPlayerOwner() == GetOverseerer()->GetPlayerOwner())
					{
						Server_SelectUnits(character);
						character->Decal->SetVisibility(true);
					}
					
				}
			}
		}
	}

}

void ADecay_of_environmentPlayerController::Server_SelectUnits_Implementation(ADecay_of_environmentCharacter* _character)
{
	selectedUnits.Add(_character);
}


void ADecay_of_environmentPlayerController::MoveUnits_Implementation(FVector loc)
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
					con->MoveAI(loc, a);
				}
			}
		}
	}
}


IDamagableInterface* ADecay_of_environmentPlayerController::GetDamagable(AActor* other)
{
	return Cast<IDamagableInterface>(other);
}

void ADecay_of_environmentPlayerController::Button1()
{
	switch (AbilitySwitcher->GetActiveWidgetIndex())
	{
	case 0:
		break;
	case 1:
		Shield();
		break;
	default:
		break;
	}
	
}

void ADecay_of_environmentPlayerController::Button2()
{
	switch (AbilitySwitcher->GetActiveWidgetIndex())
	{
	case 0:
		break;
	case 1:
		DashAbility();
		break;
	default:
		break;
	}
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
	if (overseerer == nullptr)
	{
		overseerer = Cast<AOverseerer>(GetPawn());
	}
	return overseerer;
}

void ADecay_of_environmentPlayerController::ZoomIn()
{
	GetOverseerer()->GetCameraBoom()->TargetArmLength -= ZoomRate;

	if (GetOverseerer()->GetCameraBoom()->TargetArmLength < MinZoom)
	{
		GetOverseerer()->GetCameraBoom()->TargetArmLength = MinZoom;
	}
}

void ADecay_of_environmentPlayerController::ZoomOut()
{
	GetOverseerer()->GetCameraBoom()->TargetArmLength += ZoomRate;

	if (GetOverseerer()->GetCameraBoom()->TargetArmLength > MaxZoom) {
		GetOverseerer()->GetCameraBoom()->TargetArmLength = MaxZoom;
	}
}

void ADecay_of_environmentPlayerController::SpawnBuilding()
{

	if (GetOverseerer()->statistics.ComponentsValue >= 10)
	{
		FVector Location;
		Location = MousePos;
		//UE_LOG(LogTemp, Warning, TEXT("Spawned at X: %d Y: %d"), Location.X, Location.Y);
		FRotator Rotation = { 0,0,0 };
		ABuildingIcon* Building = GetWorld()->SpawnActor<ABuildingIcon>(BuildingIconToSpawn, Location, Rotation);
		/*Building->spawn;*/
		/*Building->buildingStats.currentHealth = 10.0f;
		Buildings.Add(Building);*/
		GetOverseerer()->statistics.ComponentsValue -= 10;
	}

}

void ADecay_of_environmentPlayerController::SpawnUnit()
{
	for (auto& Building : Buildings)
	{
		if (Building->IsMainBuilding)
		{
			if (GetOverseerer()->statistics.ComponentsValue >= 10)
			{
				FVector Location = Building->GetActorLocation();
				Location.X = Location.X + 20;
				UE_LOG(LogTemp, Warning, TEXT("Spawned at X: %d Y: %d"), Location.X, Location.Y);
				FRotator Rotation = { 0,0,0 };
				GetWorld()->SpawnActor<AActor>(UnitToSpawn, Location, Rotation);
				GetOverseerer()->statistics.ComponentsValue -= 10;
				break;

			}
		}
	}
}

void ADecay_of_environmentPlayerController::Shield()
{
	AbilityManager->Shield(selectedUnits);
	/*for (ADecay_of_environmentCharacter* units : selectedUnits)
	{
		if (units->stats.unitID == 1)
		{
			if (units->stats.Energy >= 5)
			{
				FVector Location = units->GetActorLocation();
				FRotator Rotation = { 0,0,0 };
				AShieldAblitity* _Shield = GetWorld()->SpawnActor<AShieldAblitity>(AbilityToSpawn, Location, Rotation);
				_Shield->SetParentActor(units);
				units->stats.Energy -= 5;
				break;
			}

		}

	}*/
}

void ADecay_of_environmentPlayerController::DashAbility()
{
	
	AbilityManager->DashAbility(selectedUnits);
	//for (ADecay_of_environmentCharacter* units : selectedUnits)
	//{
	//	if (units->stats.unitID == 1)
	//	{
	//		if (units->stats.Energy >= 5)
	//		{
	//			FVector Location = units->GetActorLocation();
	//			FRotator Rotation = { 0,0,0 };
	//			ADash* _Dash = GetWorld()->SpawnActor<ADash>(Dash, Location, Rotation);
	//			_Dash->SetParentActor(units);
	//			units->stats.Energy -= 5;
	//			//units->SetActorLocation(FVector(100,100,1));
	//			break;
	//		}

	//	}

	//}
}

UMissionDataAsset* ADecay_of_environmentPlayerController::GetMissionDataAsset()
{
	UMissionDataAsset* MissionDataAsset = LoadObject<UMissionDataAsset>(NULL, TEXT("/Game/TopDown/Blueprints/DataAssetMissions/MissionDataAsset"));
	return MissionDataAsset;
}


void ADecay_of_environmentPlayerController::SpawnUnBuiltBuilding(FVector location, FRotator rotation)
{
	m_Building = GetWorld()->SpawnActor<AUnbuiltBuilding>(UnbuiltBuildingToSpawn, location, rotation);
	Server_SpawnBuilding(location, rotation);
}

void ADecay_of_environmentPlayerController::Server_SpawnBuilding_Implementation(FVector location, FRotator rotation)
{
	m_Building = GetWorld()->SpawnActor<AUnbuiltBuilding>(UnbuiltBuildingToSpawn, location, rotation);
	//Building->SetOwner(_overseerer);
	Multicast_SpawnBuilding(location, rotation);

}

void ADecay_of_environmentPlayerController::Multicast_SpawnBuilding_Implementation(FVector location, FRotator rotation)
{
	m_Building = GetWorld()->SpawnActor<AUnbuiltBuilding>(UnbuiltBuildingToSpawn, location, rotation);
	//Building->SetOwner(_overseerer);
}

void ADecay_of_environmentPlayerController::Client_SpawnBuilding_Implementation(FVector location, FRotator rotation)
{
	Server_SpawnBuilding(location, rotation);
}

