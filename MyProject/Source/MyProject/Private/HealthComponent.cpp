// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TurretPawn.h"
#include "DronePawn.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;
	Health -= Damage;
	if (Health <= 0) {
		if (Cast<ATurretPawn>(GetOwner()))
		{
			GetOwner()->Destroy();
		}
		else if (Cast<ADronePawn>(GetOwner()))
		{
			UE_LOG(LogTemp, Error, TEXT("Player died"));
			GetOwner()->DisableInput(Cast<ADronePawn>(GetOwner())->GetDroneController());
			Cast<ADronePawn>(GetOwner())->bAlive = false;
		}
	}
}