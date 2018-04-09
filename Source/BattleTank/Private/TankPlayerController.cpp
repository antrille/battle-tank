// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
	}

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::SetPlayerUiReference(UUserWidget * UserWidget)
{
	PlayerUiWidget = UserWidget;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent))
		{
			return;
		}

		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	if (!ensure(PlayerUiWidget))
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

	if (!ensure(AimPointWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("AimPoint widget is not found"));
		return false;
	}

	// Получаем координаты прицела на экране
	auto RootGeometry = PlayerUiWidget->GetCachedGeometry();
	auto AimPointGeometry = AimPointWidget->GetCachedGeometry();

	auto ScreenPosition = RootGeometry.AbsoluteToLocal(AimPointGeometry.GetAbsolutePosition());

	// Добавляем половину размера прицела к результирующей позиции, чтобы она приходилась на центр виджета
	ScreenPosition += AimPointGeometry.GetLocalSize() * .5f;

	// Применяем к позиции DPI масштабирование UI
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


