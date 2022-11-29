// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagableInterface.h"

// Add default functionality here for any IDamagableInterface functions that are not pure virtual.
void IDamagableInterface::TakeDamage(float damage)
{

}

float IDamagableInterface::GetHealth()
{
	return 1.0f;
}

float IDamagableInterface::GetMaxHealth()
{
	return 1.0f;
}