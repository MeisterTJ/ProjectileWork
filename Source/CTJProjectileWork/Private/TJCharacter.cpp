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
			// UIWidget�� ������Ÿ�� ���ڵ� ���ε� �� ĳ���͵�������Ʈ�� UIWidget�� �Լ� ���
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

// �߻� ���� �ʱ�ȭ
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
		// �����ð��� ���� �Ϲ� Ȥ�� ���� �߻�ü �߻�
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

// ATJProjectile subclass�� UClass�� �����Ͽ� ���� �� �߻��ϴ� �Լ�
void ATJCharacter::FireProjectile(TSubclassOf<ATJProjectile> ProjectileClass, EProjectileType eType)
{
	UWorld* World = GetWorld();

	if ( World )
	{
		// ������ z(�����߾�) - ĸ��������Ʈ�� halfheight + 50.0f �� �߻�� z��ġ
		float fFeetToUpward = UPWARD_OFFSET - GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		// ������Ÿ�� CDO�� ������� ���忡 ���͸� ���� (ĳ���� ���� �������� x 20, z 50)
		ATJProjectile* Projectile = World->SpawnActor<ATJProjectile>(ProjectileClass, GetActorLocation() + GetActorForwardVector() * FORWARD_OFFSET + FVector(0.0f, 0.0f, fFeetToUpward), GetActorRotation());
		ProjectileRecord->AddProjectileCount(eType);
	}

	InitFireState();
}
