// Fill out your copyright notice in the Description page of Project Settings.


#include "TJProjectile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATJProjectile::ATJProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	// �ڽ� ������Ʈ�� ��Ʈ���� OnComponentHit�� ����� �����Ѵ�.
	RootComponent = BoxComponent;
	// Projectile �������� �����߰�, �̸� �����Ѵ�.
	BoxComponent->SetCollisionProfileName(TEXT("Projectile"));
	// �ڽ� ������Ʈ ũ��
	BoxComponent->SetBoxExtent(FVector(40.0f, 5.0f, 5.0f));
	// �ڽ� ������Ʈ�� pivot�� �ڽ��� �߾��̱� ������ extent�� x��ŭ ������ �̵�
	BoxComponent->SetRelativeLocation(FVector(40.0f, 0.0f, 0.0f));

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	// root�� relative�� ��ġ
	ArrowComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 0.0f));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);

	// �ӵ� 100
	ProjectileMovementComponent->InitialSpeed = 100.0f;
	ProjectileMovementComponent->MaxSpeed = 100.0f;
	// ���ν�Ƽ ���⿡ ���� ȸ��
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	// �߷��� 0����
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
	// 3�� �� ����
	InitialLifeSpan = 3.0f;
}

void ATJProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Dynamic Delegate�� �浹�� ���Ͽ� OnHit �Լ��� ȣ���Ѵ�.
	BoxComponent->OnComponentHit.AddDynamic(this, &ATJProjectile::OnHit);

	// Arrow, Box �� �� �ΰ��ӿ��� ���̵��� ����
	ArrowComponent->SetHiddenInGame(false);
	BoxComponent->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ATJProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATJProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATJProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	Destroy();
}


