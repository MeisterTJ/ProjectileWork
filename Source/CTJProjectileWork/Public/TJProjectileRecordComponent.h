// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TJProjectileRecordComponent.generated.h"

// 등록된 함수들에게 브로드캐스팅하는 멀티캐스트 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnCountChangeDelegate);

// 프로젝타일 발사 개수를 기록하는 컴포넌트
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CTJPROJECTILEWORK_API UTJProjectileRecordComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTJProjectileRecordComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	const TArray<int32>* GetCountArray() const;
	void AddProjectileCount(enum class EProjectileType eType, int32 count = 1);
	void ResetProjectileCounts();

	// Delegate는 typename 앞에 F를 붙여야 한다.
	FOnCountChangeDelegate OnCountChanged;

private:
	UPROPERTY(Transient)
	TArray<int32> CountArray;
};
