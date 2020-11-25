// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TJProjectile.h"
#include "TJSplitProjectile.generated.h"

// 분열 발사체
UCLASS()
class CTJPROJECTILEWORK_API ATJSplitProjectile : public ATJProjectile
{
	GENERATED_BODY()
	
public:
	ATJSplitProjectile();

public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Component)
	UArrowComponent* LeftArrowComponent;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UArrowComponent* RightArrowComponent;

	// 타이머 핸들
	FTimerHandle SplitTimerHandle;

	// 3초에 분열
	const float fSplitTime = 3.0f;
};
