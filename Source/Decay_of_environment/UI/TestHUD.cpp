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

void ATestHUD::BeginPlay()
{
	
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Adding player"));
	if (!ensure(UserInterfaceClass != nullptr)) return;
	UserInterface = CreateWidget<UUserInterface>(GetWorld(), UserInterfaceClass);
	if (!ensure(UserInterface != nullptr)) return;

	UserInterface->Setup();
}
