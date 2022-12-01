// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManuInterface.h"
#include "MenuWidget.generated.h"


/**
 *
 */
UCLASS()
class DECAY_OF_ENVIRONMENT_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup();
	void Teardown();
	void SetMenuInterface(IManuInterface* MenuInterface);

protected:
	IManuInterface* MenuInterface;
};
