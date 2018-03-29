// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: Player tank is not found."));
		return;
	}

	auto HitLocation = PlayerTank->GetActorLocation();
	GetControlledTank()->AimAt(HitLocation);
}

ATank* ATankAIController::GetControlledTank() const
{
	// Cast function already has a nullptr check inside
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();

	return PlayerController ? Cast<ATank>(PlayerController->GetPawn()) : nullptr;
}