// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shooter_BaseObject.h"
#include "DronePawn.generated.h"

/**
 * 
 */
UCLASS()
class ADronePawn : public AShooter_BaseObject
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// Sets default values for this pawn's properties
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	APlayerController* GetDroneController() const { return DronePlayerController; }
	ADronePawn();

private:

	UPROPERTY(EditAnywhere, category = "Movement")
	float Speed = 50.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 50.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RiseRate = 20.f;

	APlayerController* DronePlayerController;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComponent;

	void MoveForward(float Value);
	void MoveSideways(float Value);
	void RiseLowerDrone(float Value);
	void RotateOnMouseMove(float Value);

public:
	bool bAlive = true;
};
