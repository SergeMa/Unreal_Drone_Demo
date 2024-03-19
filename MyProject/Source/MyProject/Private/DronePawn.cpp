#include "DronePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"

ADronePawn::ADronePawn() {
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(Super::TurretMesh);
}

void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &ADronePawn::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ADronePawn::MoveSideways);
	PlayerInputComponent->BindAxis("RiseLowerDrone", this, &ADronePawn::RiseLowerDrone);
	PlayerInputComponent->BindAxis("RotateTurret", this, &ADronePawn::RotateOnMouseMove);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ADronePawn::Shoot);
}

void ADronePawn::BeginPlay() {
	Super::BeginPlay();

	DronePlayerController = Cast<APlayerController>(GetController());
}

void ADronePawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	/*
	if (InfoWidget) {
		InfoWidget->AddToViewport();
	}
	*/

	FRotator Flatten = GetActorRotation();
	Flatten.Roll = 0;
	SetActorRotation(Flatten);
}

void ADronePawn::MoveForward(float Value) {
	AddActorLocalOffset(FVector(Speed * Value, 0, 0), true);
}

void ADronePawn::MoveSideways(float Value) {
	AddActorLocalOffset(FVector(0, Speed * Value, 0), true);
}

void ADronePawn::RiseLowerDrone(float Value) {
	AddActorLocalOffset(FVector(0, 0, RiseRate * Value), true);
}

void ADronePawn::RotateOnMouseMove(float Value) {
	if (DronePlayerController)
	{
		float MouseX, MouseY;
		GetDroneController()->GetInputMouseDelta(MouseX, MouseY);
		FRotator Rotation = FRotator(MouseY * TurnRate, MouseX * TurnRate, 0);
		AddActorLocalRotation(Rotation, true);
	}
}