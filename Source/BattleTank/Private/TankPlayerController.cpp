// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	
	if (!Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *Tank->GetName());
	} 
}

ATank* ATankPlayerController::GetControlledTank() const
{
	// Cast function already has a nullptr check inside
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	const auto Tank = GetControlledTank();
	if (! Tank)
	{
		return;
	}
	
	FHitResult HitResult;
	if (GetSightRayHitLocation(HitResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitResult.ToString());
	}


}

bool ATankPlayerController::GetSightRayHitLocation(FHitResult& HitResult) const
{
	auto Viewport = GetWorld()->GetGameViewport();

	FVector2D ViewportSize;
	Viewport->GetViewportSize(ViewportSize);
	
	if (!IsValid(AimPointWidget))
	{
		return false;
	}

	auto RootGeometry = AimPointWidget->GetCachedGeometry();
	auto AimPointGeometry = AimPointWidget->WidgetTree->FindWidget("AimPoint")->GetCachedGeometry();
	
	auto Coords = RootGeometry.AbsoluteToLocal(AimPointGeometry.GetAbsolutePosition());

	// TODO: Find scale 

	UE_LOG(LogTemp, Warning, TEXT("Screen: %s; Ray: %s"), *ViewportSize.ToString(), *Coords.ToString());

	return false;
}



