// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* StaticMeshComponent)
{
	Barrel = StaticMeshComponent;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* StaticMeshComponent)
{
	Turret = StaticMeshComponent;
}

void UTankAimingComponent::AimAt(FVector Location, float LaunchSpeed) const
{
	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel reference is not set."));
		return;
	}

	if (!Turret)
	{
		UE_LOG(LogTemp, Warning, TEXT("Turret reference is not set."));
		return;
	}


	const auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector LaunchVelocity;

	const auto Result = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		LaunchVelocity, 
		StartLocation, 
		Location, 
		LaunchSpeed, 
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (!Result)
	{
		return;
	}

	auto AimDirection = LaunchVelocity.GetSafeNormal();
	const auto AimRotation = AimDirection.Rotation();

	Barrel->Elevate(FRotator(AimRotation.Pitch, 0, 0));
	Turret->Rotate(FRotator(0, AimRotation.Yaw, 0));
}