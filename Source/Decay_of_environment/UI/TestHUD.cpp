// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHUD.h"
#include "UserInterface.h"
#include <UObject/ConstructorHelpers.h>

ATestHUD::ATestHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UserInterfaceBPClass(TEXT("/Game/TopDown/Blueprints/BP_UserInterface"));
	if (!ensure(UserInterfaceBPClass.Class != nullptr)) return;

	UserInterfaceClass = UserInterfaceBPClass.Class;
}

void ATestHUD::DrawHUD()
{
	if (PlayerController->leftMouseDown)
	{
		SelectedActors.Empty();
		FLinearColor SelectionBoxColor;
		SelectionBoxColor.R = 0;
		SelectionBoxColor.G = 255;
		SelectionBoxColor.B = 0;
		SelectionBoxColor.A = 0.4;

		double EndPosX = PlayerController->MouseEndX - PlayerController->MouseStartX;
		double EndPosY = PlayerController->MouseEndY - PlayerController->MouseStartY;
		DrawRect(SelectionBoxColor, PlayerController->MouseStartX, PlayerController->MouseStartY, EndPosX, EndPosY);
		
		GetActorsInSelectionRectangle(FVector2D(PlayerController->MouseStartX, PlayerController->MouseStartY), FVector2D(PlayerController->MouseEndX, PlayerController->MouseEndY), SelectedActors);
	}
}

void ATestHUD::BeginPlay()
{
	
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Adding player"));
	if (!ensure(UserInterfaceClass != nullptr)) return;
	UserInterface = CreateWidget<UUserInterface>(GetWorld(), UserInterfaceClass);
	if (!ensure(UserInterface != nullptr)) return;

	UserInterface->Setup();
	PlayerController = Cast<ADecay_of_environmentPlayerController>(GetWorld()->GetFirstPlayerController());
	
}

void ATestHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PlayerController->AbilitySwitcher = UserInterface->GetAbilitySwitcher();
	

	UserInterface->UpdateText();
	for (auto character : PlayerController->GetUnitsArray())
	{
		switch (character->stats.unitID)
		{
		case 0:
			UserInterface->SwitchAbilities(UserInterface->WorkerAbilities);
			break;
		case 1:
			UserInterface->SwitchAbilities(UserInterface->ArmyAbilities);
			break;
		default:
			break;
		}
	}

	
}

void ATestHUD::PressAbiltiy1()
{
	UserInterface->Ability1;
}


