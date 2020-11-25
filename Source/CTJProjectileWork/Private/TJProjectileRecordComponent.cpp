// Fill out your copyright notice in the Description page of Project Settings.


#include "TJProjectileRecordComponent.h"
#include "TJProjectile.h"

// Sets default values for this component's properties
UTJProjectileRecordComponent::UTJProjectileRecordComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;

	CountArray.Init(0, static_cast<int>(EProjectileType::END));
}


// Called when the game starts
void UTJProjectileRecordComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTJProjectileRecordComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

const TArray<int32>* UTJProjectileRecordComponent::GetCountArray() const
{
	return &CountArray;
}

void UTJProjectileRecordComponent::AddProjectileCount(EProjectileType eType, int32 count)
{
	int32 index = static_cast<int>(eType);
	if ( index < CountArray.Num() )
	{
		CountArray[index] += count;
		OnCountChanged.Broadcast();
	}
}

void UTJProjectileRecordComponent::ResetProjectileCounts()
{
	CountArray.Init(0, CountArray.Num());
	OnCountChanged.Broadcast();
}

