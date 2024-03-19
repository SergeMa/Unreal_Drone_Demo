// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter_BaseObject.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
AShooter_BaseObject::AShooter_BaseObject()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	RootComponent = BaseCollider;
	

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(BaseCollider);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}


void AShooter_BaseObject::LookAt(FVector LookAtTarget) {
	FVector Direction = LookAtTarget - TurretMesh->GetComponentLocation();
	Direction.Z -= 100;
	Direction.Normalize();
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 25.f));
}

void AShooter_BaseObject::Shoot() {
	if (AmmoCount > 0 || AmmoCount <= -1) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		Projectile->SetOwner(this);
		AmmoCount--;
	}
}