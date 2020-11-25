// Fill out your copyright notice in the Description page of Project Settings.


#include "TJUIWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TJProjectileRecordComponent.h"
#include "TJProjectile.h"
#include "TJCharacter.h"
#include "Math/UnrealMathUtility.h"

void UTJUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ChargeWidget = Cast<UWidget>(GetWidgetFromName(TEXT("VB_ChargeUI")));
	ChargeGauge = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_ChargeGauge")));
	ProgressTime = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ProgressTime")));
	ChargeWidget->SetVisibility(ESlateVisibility::Hidden);

	A1Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_A1Count")));
	A2Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_A2Count")));
	A3Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_A3Count")));
	A4Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_A4Count")));
	Reset = Cast<UButton>(GetWidgetFromName(TEXT("ResetBtn")));

	// Dynamic delegate는 직렬화되어 BP에서 사용이 가능하다.
	Reset->OnClicked.AddDynamic(this, &UTJUIWidget::ResetProjectileRecord);
}

// 프로그레스 바를 업데이트한다. 
void UTJUIWidget::UpdateChargeProgress(float fProgressTime)
{
	constexpr float CHARGE_TIME = 3.0f;
	float progress = FMath::Clamp(fProgressTime, 0.0f, CHARGE_TIME) / CHARGE_TIME;
	ProgressTime->SetText(FText::AsPercent(progress));
	ChargeGauge->SetPercent(progress);
}

// 프로젝타일 기록 UI를 업데이트
void UTJUIWidget::UpdateProjectileRecordUI()
{
	const TArray<int32>* CountArray = ProjectileRecord->GetCountArray();
	
	if ( CountArray && CountArray->Num() == static_cast<int>(EProjectileType::END))
	{
		A1Count->SetText(FText::AsNumber((*CountArray)[static_cast<int>(EProjectileType::NORMAL)]));
		A2Count->SetText(FText::AsNumber((*CountArray)[static_cast<int>(EProjectileType::CHARGE)]));
		A3Count->SetText(FText::AsNumber((*CountArray)[static_cast<int>(EProjectileType::SPLIT)]));
		A4Count->SetText(FText::AsNumber((*CountArray)[static_cast<int>(EProjectileType::REFLECT)]));
	}
}

// 프로젝타일 기록을 초기화
void UTJUIWidget::ResetProjectileRecord()
{
	ProjectileRecord->ResetProjectileCounts();
}

void UTJUIWidget::BindProjectileRecord(UTJProjectileRecordComponent* _ProjectileRecord)
{
	ProjectileRecord = _ProjectileRecord;
	// 프로젝타일 레코드의 델리게이트에 함수 바인드
	ProjectileRecord->OnCountChanged.AddUObject(this, &UTJUIWidget::UpdateProjectileRecordUI);
}

// 플레이어의 Delegate에 등록
void UTJUIWidget::BindToCharacterDelegate(ATJCharacter * Character)
{
	// 람다로 바인드
	Character->OnChargeStateChanged.BindLambda([this](bool isCharge)->void
	{
		ChargeWidget->SetVisibility(isCharge ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	});

	// 함수를 바인드
	Character->OnChargeTimeChanged.BindUFunction(this, FName("UpdateChargeProgress"));
}