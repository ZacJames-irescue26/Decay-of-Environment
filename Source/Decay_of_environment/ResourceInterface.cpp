// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceInterface.h"

// Add default functionality here for any IResourceInterface functions that are not pure virtual.

FString IResourceInterface::GetEnumName()
{
	return UEnums_Structs::EnumToString(TEXT("EResourceType"), static_cast<uint8>(GetType()));
}

void IResourceInterface::TakeResources(int32 amount)
{
}

EResourceType IResourceInterface::GetType()
{
	return EResourceType::Components;
}

int32 IResourceInterface::GetAmount()
{
	return 0;
}