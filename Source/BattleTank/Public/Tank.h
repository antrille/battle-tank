// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

#pragma region Forward declarations

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

#pragma endregion

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	UPROPERTY(EditAnywhere, Category=Firing)
	float LaunchSpeed = 10000; // 1000 m/s

	void AimAt(FVector Location) const;

	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel* StaticMeshComponent) const;

	UFUNCTION(BlueprintCallable)
	void SetTurretReference(UTankTurret* StaticMeshComponent) const;

protected:
	UTankAimingComponent* AimingComponent = nullptr;

	void BeginPlay() override;

public:	
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
