// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TJProjectileRecordComponent.generated.h"

// ��ϵ� �Լ��鿡�� ��ε�ĳ�����ϴ� ��Ƽĳ��Ʈ ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnCountChangeDelegate);

// ������Ÿ�� �߻� ������ ����ϴ� ������Ʈ
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

	// Delegate�� typename �տ� F�� �ٿ��� �Ѵ�.
	FOnCountChangeDelegate OnCountChanged;

private:
	UPROPERTY(Transient)
	TArray<int32> CountArray;
};
