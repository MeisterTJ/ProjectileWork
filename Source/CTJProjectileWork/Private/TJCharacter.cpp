// Fill out your copyright notice in the Description page of Project Settings.


#include "TJCharacter.h"
#include "TJProjectile.h"
#include "TJChargeProjectile.h"
#include "TJSplitProjectile.h"
#include "TJReflectProjectile.h"
#include "TJPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "TJProjectileRecordComponent.h"
#include "TJUIWidget.h"

ATJCharacter::ATJCharacter()
{
	ProjectileRecord = CreateDefaultSubobject<UTJProjectileRecordComponent>(TEXT("ProjectileRecord"));
}

void ATJCharacter::BeginPlay()
{
	Super::BeginPlay();

	ATJPlayerController* PlayerController = Cast<ATJPlayerController>(GetController());
	
	if ( PlayerController )
	{
		UTJUIWidget* UIWidget = PlayerController->GetUIWidget();

		if ( UIWidget )
		{
			// UIWidget에 프로젝타일 레코드 바인드 및 캐릭터델리게이트에 UIWidget의 함수 등록
			UIWidget->BindToCharacterDelegate(this);
			UIWidget->BindProjectileRecord(ProjectileRecord);
		}
	}
}

void ATJCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( bPressFire1 )
	{
		fChargeTime += DeltaTime;
		OnChargeTimeChanged.Execute(fChargeTime);
	}
}

void ATJCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire1", IE_Pressed, this, &ATJCharacter::Fire1Pressed);
	PlayerInputComponent->BindAction("Fire1", IE_Released, this, &ATJCharacter::Fire1Release);
	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &ATJCharacter::Fire2Pressed);
	PlayerInputComponent->BindAction("Fire2", IE_Released, this, &ATJCharacter::Fire2Release);
}

// 발사 상태 초기화
void ATJCharacter::InitFireState()
{
	bPressFire1 = false;
	bPressFire2 = false;
	fChargeTime = 0.0f;
	OnChargeStateChanged.Execute(false);
	OnChargeTimeChanged.Execute(0.0f);
}

void ATJCharacter::Fire1Pressed()
{
	bPressFire1 = true;
	bPressFire2 = false;
	fChargeTime = 0.0f;
	OnChargeStateChanged.Execute(true);
	OnChargeTimeChanged.Execute(0.0f);
}

void ATJCharacter::Fire1Release()
{
	//UE_LOG(LogClass, Warning, TEXT("Release Charge : %f"), fChargeTime);
	if ( bPressFire1 )
	{
		// 충전시간에 따라 일반 혹은 충전 발사체 발사
		if ( fChargeTime >= CHARGE_FIRE_TIME )
		{
			FireProjectile(ATJChargeProjectile::StaticClass(), EProjectileType::CHARGE);
		}
		else
		{
			FireProjectile(ATJProjectile::StaticClass(), EProjectileType::NORMAL);
		}
	}
}

void ATJCharacter::Fire2Pressed()
{
	if ( bPressFire1 && fChargeTime <= SPLIT_FIRE_TIME )
	{
		FireProjectile(ATJSplitProjectile::StaticClass(), EProjectileType::SPLIT);
	}
	else
	{
		InitFireState();
		bPressFire2 = true;
	}
}

void ATJCharacter::Fire2Release()
{
	if ( bPressFire2 )
	{
		FireProjectile(ATJReflectProjectile::StaticClass(), EProjectileType::REFLECT);
	}
}

// ATJProjectile subclass의 UClass를 전달하여 생성 후 발사하는 함수
void ATJCharacter::FireProjectile(TSubclassOf<ATJProjectile> ProjectileClass, EProjectileType eType)
{
	UWorld* World = GetWorld();

	if ( World )
	{
		// 액터의 z(몸통중앙) - 캡슐컴포넌트의 halfheight + 50.0f 가 발사될 z위치
		float fFeetToUpward = UPWARD_OFFSET - GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		// 프로젝타일 CDO를 기반으로 월드에 액터를 스폰 (캐릭터 전방 방향으로 x 20, z 50)
		ATJProjectile* Projectile = World->SpawnActor<ATJProjectile>(ProjectileClass, GetActorLocation() + GetActorForwardVector() * FORWARD_OFFSET + FVector(0.0f, 0.0f, fFeetToUpward), GetActorRotation());
		ProjectileRecord->AddProjectileCount(eType);
	}

	InitFireState();
}
