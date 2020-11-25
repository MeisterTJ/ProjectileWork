// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TJProjectile.generated.h"

enum class EProjectileType
{
	NORMAL = 0,
	CHARGE,
	SPLIT,
	REFLECT,
	END,
};

// 일반 발사체
UCLASS()
class CTJPROJECTILEWORK_API ATJProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATJProjectile();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// 화살표
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UArrowComponent* ArrowComponent;

	// 충돌체 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UBoxComponent* BoxComponent;

	// 프로젝타일 무브 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UProjectileMovementComponent* ProjectileMovementComponent;
};
