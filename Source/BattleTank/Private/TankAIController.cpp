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

	const auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: Player tank is not found."));
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	const auto ControlledTank = Cast<ATank>(GetPawn());
	const auto HitLocation = PlayerTank->GetActorLocation();

	ControlledTank->AimAt(HitLocation);
	ControlledTank->Fire();
}