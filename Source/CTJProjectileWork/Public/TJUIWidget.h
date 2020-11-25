// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TJUIWidget.generated.h"


// UI를 컨트롤하는 클래스 
UCLASS()
class CTJPROJECTILEWORK_API UTJUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindProjectileRecord(class UTJProjectileRecordComponent* _ProjectileRecord);
	void BindToCharacterDelegate(class ATJCharacter* Character);
	
protected:
	virtual void NativeConstruct() override;

private:
	void UpdateProjectileRecordUI();

	// Delegate가 호출하는 함수는 UFUNCTION이어야 한다. 
	UFUNCTION()
	void UpdateChargeProgress(float fProgressTime);
	UFUNCTION()
	void ResetProjectileRecord();

private:
	// 레퍼런스 카운팅이 올라가지 않는 참조
	TWeakObjectPtr<class UTJProjectileRecordComponent> ProjectileRecord;

	UPROPERTY()
	class UWidget* ChargeWidget;

	UPROPERTY()
	class UProgressBar* ChargeGauge;

	UPROPERTY()
	class UTextBlock* ProgressTime;

	UPROPERTY()
	class UButton* Reset;

	UPROPERTY()
	class UTextBlock* A1Count;

	UPROPERTY()
	class UTextBlock* A2Count;

	UPROPERTY()
	class UTextBlock* A3Count;

	UPROPERTY()
	class UTextBlock* A4Count;
};
