// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionSelectWidget.h"
#include <UObject/ConstructorHelpers.h>

UMissionSelectWidget::UMissionSelectWidget(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MissionIconBPClass(TEXT("/Game/TopDown/Blueprints/MenuSystem/BP_MissionIcon"));
	if (!ensure(MissionIconBPClass.Class != nullptr)) return;

	MissionIconClass = MissionIconBPClass.Class;
}

void UMissionSelectWidget::MissionBoxUpdate()
{
	UMissionSelectIcon* Mission = CreateWidget<UMissionSelectIcon>(GetWorld(), MissionIconClass);
	MissionSelectBox->AddChild(Mission);
}
