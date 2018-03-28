// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"

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
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToCompactString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	if (!IsValid(PlayerUiWidget))
	{
		return false;
	}

	FVector AimDirection;
	if (!GetAimPointWorldDirection(AimDirection))
	{
		return false;
	}

	auto CameraPosition = PlayerCameraManager->GetCameraLocation();
	auto LineTraceEnd = CameraPosition + (AimDirection * 1000000.f);

	FHitResult HitResult;
	if (!GetWorld()->LineTraceSingleByChannel(HitResult, CameraPosition, LineTraceEnd, ECC_Visibility))
	{
		HitLocation = FVector(.0f);
		return false;
	}

	HitLocation = HitResult.Location;

	return true;
}

bool ATankPlayerController::GetAimPointWorldDirection(FVector& AimDirection) const
{
	auto ViewportClient = GetWorld()->GetGameViewport();
	auto AimPointWidget = PlayerUiWidget->WidgetTree->FindWidget("AimPoint");

	if (!IsValid(AimPointWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("AimPoint widget is not found"));
		return false;
	}

	// Get aiming point screen coordinates
	auto RootGeometry = PlayerUiWidget->GetCachedGeometry();
	auto AimPointGeometry = AimPointWidget->GetCachedGeometry();

	auto ScreenPosition = RootGeometry.AbsoluteToLocal(AimPointGeometry.GetAbsolutePosition());

	// Apply viewport scaling factor
	auto WidgetLayoutLibrary = NewObject<UWidgetLayoutLibrary>(UWidgetLayoutLibrary::StaticClass());
	auto Scale = WidgetLayoutLibrary->GetViewportScale(ViewportClient);

	ScreenPosition *= Scale;

	FVector WorldPosition;
	FVector ProjectedVector;

	if (!DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldPosition, AimDirection))
	{
		UE_LOG(LogTemp, Error, TEXT("Can't deproject aim direction"));
		return false;
	}

	return true;
}


