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
	// 박스 컴포넌트가 루트여야 OnComponentHit가 제대로 동작한다.
	RootComponent = BoxComponent;
	// Projectile 프리셋을 생성했고, 이를 지정한다.
	BoxComponent->SetCollisionProfileName(TEXT("Projectile"));
	// 박스 컴포넌트 크기
	BoxComponent->SetBoxExtent(FVector(40.0f, 5.0f, 5.0f));
	// 박스 컴포넌트는 pivot이 박스의 중앙이기 때문에 extent의 x만큼 앞으로 이동
	BoxComponent->SetRelativeLocation(FVector(40.0f, 0.0f, 0.0f));

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	// root에 relative한 위치
	ArrowComponent->SetRelativeLocation(FVector(-40.0f, 0.0f, 0.0f));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);

	// 속도 100
	ProjectileMovementComponent->InitialSpeed = 100.0f;
	ProjectileMovementComponent->MaxSpeed = 100.0f;
	// 벨로시티 방향에 따른 회전
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	// 중력은 0으로
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
	// 3초 후 삭제
	InitialLifeSpan = 3.0f;
}

void ATJProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Dynamic Delegate로 충돌에 대하여 OnHit 함수를 호출한다.
	BoxComponent->OnComponentHit.AddDynamic(this, &ATJProjectile::OnHit);

	// Arrow, Box 둘 다 인게임에서 보이도록 설정
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


