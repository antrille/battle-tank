// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: Player tank is not found."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: Player tank name: %s"), *PlayerTank->GetName());
	}
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