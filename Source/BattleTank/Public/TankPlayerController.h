// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#pragma region Forward declarations

class ATank;

#pragma endregion

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	void Tick(float DeltaSeconds) override;
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerUiReference(UUserWidget* UserWidget);

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:	
	UUserWidget * PlayerUiWidget = nullptr;

	void AimTowardsCrosshair() const;
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetAimPointWorldDirection(FVector& AimDirection) const;
};
