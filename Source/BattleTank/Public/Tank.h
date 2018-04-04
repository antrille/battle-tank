// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

#pragma region Forward declarations

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

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
	void Fire();

	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel* StaticMeshComponent);

	UFUNCTION(BlueprintCallable)
	void SetTurretReference(UTankTurret* StaticMeshComponent);

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* MovementComponent = nullptr;

	UTankAimingComponent* AimingComponent = nullptr;

	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category=Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category=Setup)
	double ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	UTankBarrel* Barrel;
};
