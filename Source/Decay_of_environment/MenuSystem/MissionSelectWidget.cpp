// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionSelectWidget.h"
#include <UObject/ConstructorHelpers.h>
#include <Kismet/GameplayStatics.h>
#include "Decay_of_environment/RTSGameInstance.h"

UMissionSelectWidget::UMissionSelectWidget(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MissionIconBPClass(TEXT("/Game/TopDown/Blueprints/MenuSystem/BP_MissionIcon"));
	if (MissionIconBPClass.Class != nullptr)
	{
		MissionIconClass = MissionIconBPClass.Class;

	}
}

void UMissionSelectWidget::MissionBoxUpdate()
{
	URTSGameInstance* GI = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI->CurrentMission == 0)
	{
		Mission = CreateWidget<UMissionSelectIcon>(GetWorld(), MissionIconClass);
		MissionSelectBox->AddChild(Mission);
		
	}
	
}

//void UMissionSelectWidget::CreateMissionButton()
//{
//	
//}
