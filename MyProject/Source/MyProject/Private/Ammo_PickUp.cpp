// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo_PickUp.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"
#include "DronePawn.h"

// Sets default values
AAmmo_PickUp::AAmmo_PickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickUp Mesh");
	RootComponent = PickUpMesh;

}

// Called when the game starts or when spawned
void AAmmo_PickUp::BeginPlay()
{
	Super::BeginPlay();
	
	PickUpMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmo_PickUp::BeginOverlap);
}

// Called every frame
void AAmmo_PickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmo_PickUp::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ADronePawn* PlayerActor = Cast<ADronePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (OtherActor == PlayerActor) {
		PlayerActor->AmmoCount += GiveBulletAmount;
		Destroy();
	}
}