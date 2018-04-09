// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#pragma region Forward declarations

class UTankAimingComponent;

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
	UFUNCTION(BlueprintImplementableEvent, Category="Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponentRef);

private:	
	UUserWidget * PlayerUiWidget = nullptr;

	void AimTowardsCrosshair() const;
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetAimPointWorldDirection(FVector& AimDirection) const;
};
