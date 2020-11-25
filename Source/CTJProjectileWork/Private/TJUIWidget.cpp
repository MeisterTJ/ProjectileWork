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

	// Dynamic delegate�� ����ȭ�Ǿ� BP���� ����� �����ϴ�.
	Reset->OnClicked.AddDynamic(this, &UTJUIWidget::ResetProjectileRecord);
}

// ���α׷��� �ٸ� ������Ʈ�Ѵ�. 
void UTJUIWidget::UpdateChargeProgress(float fProgressTime)
{
	constexpr float CHARGE_TIME = 3.0f;
	float progress = FMath::Clamp(fProgressTime, 0.0f, CHARGE_TIME) / CHARGE_TIME;
	ProgressTime->SetText(FText::AsPercent(progress));
	ChargeGauge->SetPercent(progress);
}

// ������Ÿ�� ��� UI�� ������Ʈ
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

// ������Ÿ�� ����� �ʱ�ȭ
void UTJUIWidget::ResetProjectileRecord()
{
	ProjectileRecord->ResetProjectileCounts();
}

void UTJUIWidget::BindProjectileRecord(UTJProjectileRecordComponent* _ProjectileRecord)
{
	ProjectileRecord = _ProjectileRecord;
	// ������Ÿ�� ���ڵ��� ��������Ʈ�� �Լ� ���ε�
	ProjectileRecord->OnCountChanged.AddUObject(this, &UTJUIWidget::UpdateProjectileRecordUI);
}

// �÷��̾��� Delegate�� ���
void UTJUIWidget::BindToCharacterDelegate(ATJCharacter * Character)
{
	// ���ٷ� ���ε�
	Character->OnChargeStateChanged.BindLambda([this](bool isCharge)->void
	{
		ChargeWidget->SetVisibility(isCharge ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	});

	// �Լ��� ���ε�
	Character->OnChargeTimeChanged.BindUFunction(this, FName("UpdateChargeProgress"));
}