// Fill out your copyright notice in the Description page of Project Settings.


#include "TJSplitProjectile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

ATJSplitProjectile::ATJSplitProjectile()
{
	// -45도 화살표
	LeftArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrowComponent"));
	LeftArrowComponent->SetupAttachment(RootComponent);
	LeftArrowComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 0.0f));
	LeftArrowComponent->SetRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));

	// +45도 화살표
	RightArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("RightArrowComponent"));
	RightArrowComponent->SetupAttachment(RootComponent);
	RightArrowComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 0.0f));
	RightArrowComponent->SetRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));

	InitialLifeSpan = 0;
}

void ATJSplitProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LeftArrowComponent->SetHiddenInGame(false);
	RightArrowComponent->SetHiddenInGame(false);
}

void ATJSplitProjectile::BeginPlay()
{
	Super::BeginPlay();

	// fSplitTime 후에 람다를 호출하는 타이머 세팅
	GetWorld()->GetTimerManager().SetTimer(SplitTimerHandle, FTimerDelegate::CreateLambda([this]()->void
	{
		UWorld* World = GetWorld();

		if ( World )
		{
			UClass* NormalProjectile = ATJProjectile::StaticClass();
			World->SpawnActor<ATJProjectile>(NormalProjectile, ArrowComponent->GetComponentLocation(), ArrowComponent->GetComponentRotation());
			World->SpawnActor<ATJProjectile>(NormalProjectile, LeftArrowComponent->GetComponentLocation(), LeftArrowComponent->GetComponentRotation());
			World->SpawnActor<ATJProjectile>(NormalProjectile, RightArrowComponent->GetComponentLocation(), RightArrowComponent->GetComponentRotation());
		}

		// 분열발사체는 파괴된다.
		Destroy();
	}), fSplitTime, false);
}

void ATJSplitProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 등록된 타이머를 제거, 제거하지 않으면 충돌 삭제 후 분열되는 문제가 발생
	GetWorld()->GetTimerManager().ClearTimer(SplitTimerHandle);
}
