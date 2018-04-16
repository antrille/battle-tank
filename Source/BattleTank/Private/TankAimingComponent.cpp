// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::AimAt(FVector Location) 
{
	if (!ensure(Barrel && Turret))
	{
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

	AimDirection = LaunchVelocity.GetSafeNormal();
	AimBarrel();
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Reloading || FiringState == EFiringState::NoAmmo)
	{
		return;
	}

	if (!ensure(Barrel && ProjectileBlueprint))
	{
		return;
	}

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
	);

	Projectile->LaunchProjectile(LaunchSpeed);
	Ammo--;
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Ammo <= 0)
	{
		FiringState = EFiringState::NoAmmo;
		return;
	}

	if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	} 
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}

	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01f);
}

void UTankAimingComponent::AimBarrel()
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}

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
