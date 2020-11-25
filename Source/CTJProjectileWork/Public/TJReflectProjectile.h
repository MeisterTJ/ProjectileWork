// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TJProjectile.h"
#include "TJReflectProjectile.generated.h"

// 반사 발사체
UCLASS()
class CTJPROJECTILEWORK_API ATJReflectProjectile : public ATJProjectile
{
	GENERATED_BODY()
	
public:
	ATJReflectProjectile();

public:
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
};
