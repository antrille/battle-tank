// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank))
	{
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	const auto ControlledTank = GetPawn();
	const auto HitLocation = PlayerTank->GetActorLocation();

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
	}

	AimingComponent->AimAt(HitLocation);
	AimingComponent->Fire();
}