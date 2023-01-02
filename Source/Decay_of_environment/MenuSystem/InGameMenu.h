// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "Components/Button.h"
#include "InGameMenu.generated.h"

/**
 *
 
 */

USTRUCT(BlueprintType)
struct FSaveData
{
	GENERATED_USTRUCT_BODY()
public:
	FString X;
	FString Y;
	FString Z;
	FString team;
	FString Owner;

};

UCLASS()
class DECAY_OF_ENVIRONMENT_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SaveButton;

	UFUNCTION()
	void CancelPressed();

	UFUNCTION()
	void QuitPressed();

	UFUNCTION()
	void SaveLevel();
};
