// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionWidget.h"

void UMissionWidget::SetupMissions()
{
	FMission mission;
	mission.MissionText = TEXT("Kill 5 enemies");
	mission.MissionObjective = 5;
	MissionMap.FindOrAdd(TEXT("Mission1"), mission);

	mission.MissionText = TEXT("Mine 50 components");
	mission.MissionObjective = 50;
	MissionMap.FindOrAdd(TEXT("Mission2"), mission);
}
