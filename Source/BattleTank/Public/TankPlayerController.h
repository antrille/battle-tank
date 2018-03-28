// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player UI Widget")
	UUserWidget* PlayerUiWidget;

private:	
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetAimPointWorldDirection(FVector& AimDirection) const;
};
