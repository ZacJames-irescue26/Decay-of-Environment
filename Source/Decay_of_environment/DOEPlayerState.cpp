// Fill out your copyright notice in the Description page of Project Settings.


#include "DOEPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Decay_of_environment/Decay_of_environmentCharacter.h"
#include "Decay_of_environment/Building.h"


void ADOEPlayerState::Server_SetPlayerOwner_Implementation(int Player)
{
	SetPlayerOwner(Player);
	
}

void ADOEPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADOEPlayerState, PlayerOwner);
	DOREPLIFETIME(ADOEPlayerState, BaseNumber);
	DOREPLIFETIME(ADOEPlayerState, BarracksNumber);
	DOREPLIFETIME(ADOEPlayerState, OwnedBuildingArray);
	DOREPLIFETIME(ADOEPlayerState, OwnedUnitArray);


	
}
