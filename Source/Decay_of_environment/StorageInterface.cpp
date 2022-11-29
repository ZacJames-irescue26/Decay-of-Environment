// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageInterface.h"

// Add default functionality here for any IStorageInterface functions that are not pure virtual.

TArray<FItem>& IStorageInterface::GetItems()
{
	return inventory.items;
}

void IStorageInterface::AddItem(FString name, int32 amount)
{
	bool itemFound = false;

	for (FItem& item : GetItems())
	{
		if (item.itemName.Equals(name))
		{
			item.amount += amount;
			itemFound = true;
			break;
		}
	}

	if (!itemFound)
	{
		FItem item;
		item.itemName = name;
		item.amount = amount;
		GetItems().Add(item);
	}
}

void IStorageInterface::RemoveItem(FString name, int32 amount)
{
	for (FItem item : GetItems())
	{
		if (item.itemName.Equals(name))
		{
			item.amount -= amount;
			break;
		}
	}
}