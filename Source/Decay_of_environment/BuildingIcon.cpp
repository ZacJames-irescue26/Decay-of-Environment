// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingIcon.h"
#include "TileGrid/CubeGridManager.h"
#include "Kismet/GameplayStatics.h"
#include "Decay_of_environmentPlayerController.h"
#include "UnbuiltBuilding.h"
#include "Decay_of_environment/Overseerer.h"
#include <Components/StaticMeshComponent.h>
#include <Engine/StaticMesh.h>
#include "Net/UnrealNetwork.h"
// Sets default values
ABuildingIcon::ABuildingIcon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
}

void ABuildingIcon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABuildingIcon, Building);
}

// Called when the game starts or when spawned
void ABuildingIcon::BeginPlay()
{
	Super::BeginPlay();
	GridManager = Cast<ACubeGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACubeGridManager::StaticClass()));
	ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(GetWorld()->GetFirstLocalPlayerFromController());
	if (PlayerController)
	{
		_overseerer = PlayerController->GetOverseerer();
		this->SetOwner(_overseerer);
	}
	
	
}

// Called every frame
void ABuildingIcon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// from tutorial
	// Get the AABB in Local space (aka Object space: such as in the Blueprint viewer). You might want to cache this result as this may be costly. 
	const FBox Box = this->GetComponentsBoundingBox(true,true);
	const auto Transform = this->GetTransform();

	// Get World space Location.
	const FVector Center = Transform.TransformPosition(Box.GetCenter());

	// And World space extent
	const FVector Extent = Box.GetExtent();
	const FVector Forward = Transform.TransformVector(FVector::ForwardVector * Extent.X);
	const FVector Right = Transform.TransformVector(FVector::RightVector * Extent.Y);
	const FVector Up = Transform.TransformVector(FVector::UpVector * Extent.Z);

	// Now you have an oriented bounding box represented by a `Center` and three extent vectors.

	const FVector ExtentsX = Right;
	const FVector ExtentsY = Up;
	const FVector ExtentsZ = Forward;

	Corner2 = Center + ExtentsX - ExtentsY + ExtentsZ;
	Corner3 = Center - ExtentsX - ExtentsY + ExtentsZ;
	Corner6 = Center + ExtentsX - ExtentsY - ExtentsZ;
	Corner7 = Center - ExtentsX - ExtentsY - ExtentsZ;

	/*UE_LOG(LogTemp, Warning, TEXT("2X: %f, Y: %f, Z: %f"), Corner2.X, Corner2.Y, Corner2.Z);
	UE_LOG(LogTemp, Warning, TEXT("3X: %f, Y: %f, Z: %f"), Corner3.X, Corner3.Y, Corner3.Z);
	UE_LOG(LogTemp, Warning, TEXT("6X: %f, Y: %f, Z: %f"), Corner6.X, Corner6.Y, Corner6.Z);
	UE_LOG(LogTemp, Warning, TEXT("7X: %f, Y: %f, Z: %f"), Corner7.X, Corner7.Y, Corner7.Z);*/

	DrawDebugLine(GetWorld(), Corner2, Corner3, FColor::Red, false, 1.0f);
	DrawDebugLine(GetWorld(), Corner3, Corner7, FColor::Red, false, 1.0f);
	DrawDebugLine(GetWorld(), Corner7, Corner6, FColor::Red, false, 1.0f);
	DrawDebugLine(GetWorld(), Corner6, Corner2, FColor::Red, false, 1.0f);
	/*LogTemp: Warning: 2X : 250.000000, Y : 250.000000, Z : -50.000000
	LogTemp : Warning : 3X : 250.000000, Y : -250.000000, Z : -50.000000
	LogTemp : Warning : 6X : -250.000000, Y : 250.000000, Z : -50.000000
	LogTemp : Warning : 7X : -250.000000, Y : -250.000000, Z : -50.000000*/


	if (!IsPlaced)
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		ADecay_of_environmentPlayerController* PlayerController = Cast<ADecay_of_environmentPlayerController>(World->GetFirstPlayerController());
		if (!ensure(PlayerController != nullptr)) return;

		//ACubeTile.GetActorLocation().X

		FVector mPos = PlayerController->MousePos;

		GridManager->GridPos.X = GridManager->AlignToGrid(mPos.X, GridManager->TileHorizontalOffset);
		GridManager->GridPos.Y = GridManager->AlignToGrid(mPos.Y, GridManager->TileVerticalOffset);
		GridManager->GridPos.Z = mPos.Z;

		//UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f Z: %f"), GridManager->GridPos.X, GridManager->GridPos.Y, GridManager->GridPos.Z);
		if (GridManager->GridPos.X / GridManager->TileHorizontalOffset >= 0 && GridManager->GridPos.Y / GridManager->TileVerticalOffset >= 0)
		{
			this->SetActorLocation(GridManager->GridPos);
			if (PlayerController->leftMouseDown)
			{
				if (PlayerController->leftMouseDown)
				{
					FVector2D Coner2Grid = FVector2D(GridManager->AlignToGrid(Corner2.X, GridManager->TileHorizontalOffset),
						GridManager->AlignToGrid(Corner2.Y, GridManager->TileVerticalOffset));
					FVector2D Coner3Grid = FVector2D(GridManager->AlignToGrid(Corner3.X, GridManager->TileHorizontalOffset),
						GridManager->AlignToGrid(Corner3.Y, GridManager->TileVerticalOffset));
					FVector2D Coner6Grid = FVector2D(GridManager->AlignToGrid(Corner6.X, GridManager->TileHorizontalOffset),
						GridManager->AlignToGrid(Corner6.Y, GridManager->TileVerticalOffset));
					FVector2D Coner7Grid = FVector2D(GridManager->AlignToGrid(Corner7.X, GridManager->TileHorizontalOffset),
						GridManager->AlignToGrid(Corner7.Y, GridManager->TileVerticalOffset));

					FVector2D GridCorner2 = GridManager->WorldToGridIndex(FVector2D(Coner2Grid.X, Coner2Grid.Y));
					FVector2D GridCorner3 = GridManager->WorldToGridIndex(FVector2D(Coner3Grid.X, Coner3Grid.Y));
					FVector2D GridCorner6 = GridManager->WorldToGridIndex(FVector2D(Coner6Grid.X, Coner6Grid.Y));
					FVector2D GridCorner7 = GridManager->WorldToGridIndex(FVector2D(Coner7Grid.X, Coner7Grid.Y));
					/*LogTemp: Warning: 2X : 250.000000, Y : 250.000000, Z : -50.000000
					LogTemp : Warning : 3X : 250.000000, Y : -250.000000, Z : -50.000000
					LogTemp : Warning : 6X : -250.000000, Y : 250.000000, Z : -50.000000
					LogTemp : Warning : 7X : -250.000000, Y : -250.000000, Z : -50.000000*/
					if (!GridManager->CheckGridIndex(GridCorner2) || !GridManager->CheckGridIndex(GridCorner7) || !GridManager->CheckGridIndex(GridCorner3) || !GridManager->CheckGridIndex(GridCorner6))
					{
						UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GetActorLocation().X, GetActorLocation().Y);
						UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner2.X, GridCorner2.Y);
						UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner3.X, GridCorner3.Y);
						UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner6.X, GridCorner6.Y);
						UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner7.X, GridCorner7.Y);


						UE_LOG(LogTemp, Warning, TEXT("Coner out of bounds"));
						return;
					}
					for (int i = GridCorner6.X; i < GridCorner2.X; i++)
					{
						for (int j = GridCorner7.Y; j < GridCorner2.Y; j++)
						{
							if (GridManager->IsOccupied(FVector2D(i, j)))
							{
								UE_LOG(LogTemp, Warning, TEXT("Grid is occupied"));
								return;
							}
						}
					}

					for (int i = GridCorner6.X; i < GridCorner2.X; i++)
					{
						for (int j = GridCorner7.Y; j < GridCorner2.Y; j++)
						{
							GridManager->CubeGrid[i][j]->IsOccupied = true;
						}
					}
					UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner2.X, GridCorner2.Y);
					UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner3.X, GridCorner3.Y);
					UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner6.X, GridCorner6.Y);
					UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), GridCorner7.X, GridCorner7.Y);
					IsPlaced = true;
					FVector location = GetActorLocation();
					FRotator rotation = GetActorRotation();
					PlayerController->SpawnUnBuiltBuilding(location, rotation);
					
					/*Client_SpawnBuilding(location, rotation);
					Server_SpawnBuilding(location, rotation);
					Server_Destroy();*/
					Destroy(true);
				}


			}
		}
	}
}


//void ABuildingIcon::Server_SpawnBuilding_Implementation(FVector location, FRotator rotation)
//{
//	Building = GetWorld()->SpawnActor<AUnbuiltBuilding>(BuildingToSpawn, location, rotation);
//	Building->SetOwner(_overseerer);
//	Multicast_SpawnBuilding(location, rotation);
//	
//}
//
//void ABuildingIcon::Multicast_SpawnBuilding_Implementation(FVector location, FRotator rotation)
//{
//	Building = GetWorld()->SpawnActor<AUnbuiltBuilding>(BuildingToSpawn, location, rotation);
//	Building->SetOwner(_overseerer);
//}
//
//void ABuildingIcon::Client_SpawnBuilding_Implementation(FVector location, FRotator rotation)
//{
//	Server_SpawnBuilding(location, rotation);
//}
//
//void ABuildingIcon::Server_Destroy_Implementation()
//{
//	this->Destroy(true);
//}

