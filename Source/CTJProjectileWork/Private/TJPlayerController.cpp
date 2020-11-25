// Fill out your copyright notice in the Description page of Project Settings.


#include "TJPlayerController.h"
#include "TJUIWidget.h"

ATJPlayerController::ATJPlayerController()
{
	// 블루프린트 위젯을 찾는다.
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
	// 위젯을 생성
	UIWidget = CreateWidget<UTJUIWidget>(this, UIWidgetClass);

	// 뷰포트에 추가
	UIWidget->AddToViewport(1);
}
