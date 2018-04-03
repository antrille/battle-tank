// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

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

void UTankAimingComponent::AimAt(FVector Location, float LaunchSpeed) 
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
	MoveBarrelTowards(AimDirection);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Always yaw the shortest way
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}