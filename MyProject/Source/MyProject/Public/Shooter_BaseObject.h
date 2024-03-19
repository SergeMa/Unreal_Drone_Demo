// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Shooter_BaseObject.generated.h"

UCLASS()
class MYPROJECT_API AShooter_BaseObject : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShooter_BaseObject();
	void LookAt(FVector LookAtTarget);
	void Shoot();

protected:


public:
	
	UPROPERTY(EditAnywhere, category = "Structure")
	class UBoxComponent* BaseCollider;
	
	UPROPERTY(EditAnywhere, category = "Structure")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, category = "Structure")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere,category = "Structure")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	int AmmoCount = -1;
};
