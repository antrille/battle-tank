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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* AimPointWidget;

private:	
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FHitResult& HitResult) const;
};
