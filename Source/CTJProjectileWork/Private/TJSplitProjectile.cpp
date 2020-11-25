// Fill out your copyright notice in the Description page of Project Settings.


#include "TJSplitProjectile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

ATJSplitProjectile::ATJSplitProjectile()
{
	// -45�� ȭ��ǥ
	LeftArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrowComponent"));
	LeftArrowComponent->SetupAttachment(RootComponent);
	LeftArrowComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 0.0f));
	LeftArrowComponent->SetRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));

	// +45�� ȭ��ǥ
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

	// fSplitTime �Ŀ� ���ٸ� ȣ���ϴ� Ÿ�̸� ����
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

		// �п��߻�ü�� �ı��ȴ�.
		Destroy();
	}), fSplitTime, false);
}

void ATJSplitProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// ��ϵ� Ÿ�̸Ӹ� ����, �������� ������ �浹 ���� �� �п��Ǵ� ������ �߻�
	GetWorld()->GetTimerManager().ClearTimer(SplitTimerHandle);
}
