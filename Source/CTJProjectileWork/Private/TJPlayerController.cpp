// Fill out your copyright notice in the Description page of Project Settings.


#include "TJPlayerController.h"
#include "TJUIWidget.h"

ATJPlayerController::ATJPlayerController()
{
	// �������Ʈ ������ ã�´�.
	static ConstructorHelpers::FClassFinder<UTJUIWidget> UI_C
	(TEXT("/Game/SideScrollerCPP/Blueprints/UI.UI_C"));

	if ( UI_C.Succeeded() )
	{
		UIWidgetClass = UI_C.Class;
	}
}

UTJUIWidget* ATJPlayerController::GetUIWidget() const
{
	return UIWidget;
}

void ATJPlayerController::BeginPlay()
{
	// ������ ����
	UIWidget = CreateWidget<UTJUIWidget>(this, UIWidgetClass);

	// ����Ʈ�� �߰�
	UIWidget->AddToViewport(1);
}
