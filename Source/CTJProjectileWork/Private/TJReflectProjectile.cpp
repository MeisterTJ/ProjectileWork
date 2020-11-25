// Fill out your copyright notice in the Description page of Project Settings.


#include "TJReflectProjectile.h"
#include "Math/UnrealMathUtility.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ATJReflectProjectile::ATJReflectProjectile()
{
	ArrowComponent->ArrowColor = FColor(0, 0, 255);

	// bShouldBounce를 켜지 않으면 contact시 시뮬레이트가 중단된다.
	ProjectileMovementComponent->bShouldBounce = true;
}


void ATJReflectProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogClass, Warning, TEXT("OnHit!"));

	// 액터의 진행방향과 부딪힌 노말로 반사 벡터를 뽑아온다.
	//FVector ReflectionVector = FMath::GetReflectionVector(GetActorForwardVector(), Hit.Normal);

	// 반사벡터를 X축으로 하는 행렬을 만들고 Rotator를 뽑아온다.
	// bShouldBounce를 true로 하면 자동으로 반대방향으로 회전하기 때문에 이 부분은 주석
	// FRotator ForwardRotator = FRotationMatrix::MakeFromX(ReflectionVector).Rotator();
	// SetActorRotation(ForwardRotator);

	// 반사는 자동으로 되지만 Velocity가 줄기 때문에 ReflectionVector 방향으로 Velocity를 다시 설정
	//ProjectileMovementComponent->Velocity = ReflectionVector * ProjectileMovementComponent->InitialSpeed;
	ProjectileMovementComponent->Velocity = -GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed;
}
