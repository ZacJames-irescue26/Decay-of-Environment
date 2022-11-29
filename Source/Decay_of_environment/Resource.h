// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceInterface.h"
#include "Resource.generated.h"




UCLASS()
class DECAY_OF_ENVIRONMENT_API AResource : public AActor, public IResourceInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	FResourceStats stats;

public:	
	virtual void TakeResources(int32 amount) override;
	virtual EResourceType GetType() override;
	virtual int32 GetAmount() override;

};
