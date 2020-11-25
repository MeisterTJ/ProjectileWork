// Fill out your copyright notice in the Description page of Project Settings.


#include "TJReflectProjectile.h"
#include "Math/UnrealMathUtility.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ATJReflectProjectile::ATJReflectProjectile()
{
	ArrowComponent->ArrowColor = FColor(0, 0, 255);

	// bShouldBounce�� ���� ������ contact�� �ùķ���Ʈ�� �ߴܵȴ�.
	ProjectileMovementComponent->bShouldBounce = true;
}


void ATJReflectProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogClass, Warning, TEXT("OnHit!"));

	// ������ �������� �ε��� �븻�� �ݻ� ���͸� �̾ƿ´�.
	//FVector ReflectionVector = FMath::GetReflectionVector(GetActorForwardVector(), Hit.Normal);

	// �ݻ纤�͸� X������ �ϴ� ����� ����� Rotator�� �̾ƿ´�.
	// bShouldBounce�� true�� �ϸ� �ڵ����� �ݴ�������� ȸ���ϱ� ������ �� �κ��� �ּ�
	// FRotator ForwardRotator = FRotationMatrix::MakeFromX(ReflectionVector).Rotator();
	// SetActorRotation(ForwardRotator);

	// �ݻ�� �ڵ����� ������ Velocity�� �ٱ� ������ ReflectionVector �������� Velocity�� �ٽ� ����
	//ProjectileMovementComponent->Velocity = ReflectionVector * ProjectileMovementComponent->InitialSpeed;
	ProjectileMovementComponent->Velocity = -GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed;
}
