// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shooter_BaseObject.h"
#include "TurretPawn.generated.h"

UCLASS()
class ATurretPawn : public AShooter_BaseObject
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurretPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	class ADronePawn* Drone;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 1000.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
	bool InFireRange();
};
