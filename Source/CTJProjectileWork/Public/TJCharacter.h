// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CTJProjectileWorkCharacter.h"
#include "TJCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnChargeStateChangeDelegate, bool);
DECLARE_DELEGATE_OneParam(FOnChargeTimeChangeDelegate, float);

UCLASS()
class CTJPROJECTILEWORK_API ATJCharacter : public ACTJProjectileWorkCharacter
{
	GENERATED_BODY()

public:
	ATJCharacter();

	FOnChargeStateChangeDelegate OnChargeStateChanged;
	FOnChargeTimeChangeDelegate OnChargeTimeChanged;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	void InitFireState();
	void Fire1Pressed();
	void Fire1Release();
	void Fire2Pressed();
	void Fire2Release();
	void FireProjectile(TSubclassOf<class ATJProjectile> ProjectileClass, enum class EProjectileType eType);

private:
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UTJProjectileRecordComponent* ProjectileRecord;

	bool bPressFire1 = false;
	bool bPressFire2 = false;
	float fChargeTime = 0.0f;

	const float SPLIT_FIRE_TIME = 1.0f;
	const float CHARGE_FIRE_TIME = 3.0f;
	const float FORWARD_OFFSET = 20.0f;
	const float UPWARD_OFFSET = 50.0f;
};