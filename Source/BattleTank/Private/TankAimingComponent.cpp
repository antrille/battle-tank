// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
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

void UTankAimingComponent::AimAt(FVector Location, float LaunchSpeed) const
{
	if (!Barrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel reference is not set."));
		return;
	}

	const auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector LaunchVelocity;

	auto Result = UGameplayStatics::SuggestProjectileVelocity(
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

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const
{
	auto DeltaRotator = AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();
	
	Barrel->Elevate(DeltaRotator.Pitch);
}