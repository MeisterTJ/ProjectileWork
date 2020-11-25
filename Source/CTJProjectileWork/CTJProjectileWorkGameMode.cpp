// Copyright Epic Games, Inc. All Rights Reserved.

#include "CTJProjectileWorkGameMode.h"
#include "CTJProjectileWorkCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "TJPlayerController.h"

ACTJProjectileWorkGameMode::ACTJProjectileWorkGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// �÷��̾� ��Ʈ�ѷ� Ŭ���� ����
	PlayerControllerClass = ATJPlayerController::StaticClass();
}
