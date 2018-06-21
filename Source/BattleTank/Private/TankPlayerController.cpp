// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent)
	{
		return;
	}

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Player tank aiming logic
	const auto PossessedTank = Cast<ATank>(GetPawn());
	if (!PossessedTank)
	{
		return;
	}

	auto AimingComponent = PossessedTank->FindComponentByClass<UTankAimingComponent>();
	if (!AimingComponent)
	{
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{		
		AimingComponent->AimAt(HitLocation);
	}
}

void ATankPlayerController::SetPlayerUiReference(UUserWidget * UserWidget)
{
	PlayerUiWidget = UserWidget;
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank)
		{
			return;
		}

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	TankDeath();

	StartSpectatingOnly();
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	FVector AimDirection;
	if (!GetAimPointWorldDirection(AimDirection))
	{
		return false;
	}

	auto CameraPosition = PlayerCameraManager->GetCameraLocation();
	auto LineTraceEnd = CameraPosition + (AimDirection * 1000000.f);

	FHitResult HitResult;
	if (!GetWorld()->LineTraceSingleByChannel(HitResult, CameraPosition, LineTraceEnd, ECC_Camera))
	{
		HitLocation = FVector(.0f);
		return false;
	}

	HitLocation = HitResult.Location;

	return true;
}

bool ATankPlayerController::GetAimPointWorldDirection(FVector& AimDirection) const
{
	if (!ensure(PlayerUiWidget))
	{
		return false;
	}

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
	auto Scale = WidgetLayoutLibrary->GetViewportScale(GetWorld()->GetGameViewport());

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


