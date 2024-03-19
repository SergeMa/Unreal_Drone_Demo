// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretPawn.h"
#include "DronePawn.h"
#include "Shooter_BaseObject.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATurretPawn::ATurretPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurretPawn::CheckFireCondition, FireRate, true);
	Drone = Cast<ADronePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange()) {
		LookAt(Drone->GetActorLocation());
	}
}

void ATurretPawn::CheckFireCondition() {
    if (Drone == nullptr)
    {
        return;
    }

    if (InFireRange() && Drone->bAlive) {
        Shoot();
    }
}

bool ATurretPawn::InFireRange() {
    if (Drone) {
        float Distance = FVector::Distance(GetActorLocation(), Drone->GetActorLocation());
        if (Distance <= AttackRange) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}


