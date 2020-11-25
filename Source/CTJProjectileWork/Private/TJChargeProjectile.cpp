// Fill out your copyright notice in the Description page of Project Settings.


#include "TJChargeProjectile.h"
#include "Components/BoxComponent.h"

ATJChargeProjectile::ATJChargeProjectile()
{
	BoxComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	BoxComponent->SetRelativeLocation(FVector(120.0f, 0.0f, 0.0f));
	InitialLifeSpan = 5.0f;
}