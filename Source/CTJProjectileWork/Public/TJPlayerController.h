// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TJPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CTJPROJECTILEWORK_API ATJPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATJPlayerController();
	class UTJUIWidget* GetUIWidget() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UTJUIWidget> UIWidgetClass;

	UPROPERTY()
	class UTJUIWidget* UIWidget;
};
