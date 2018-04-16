// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

#pragma region Forward declarations

class UTankBarrel;
class UTankTurret;
class AProjectile;

#pragma endregion

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

/**
 * Class with tank aiming and firing logic
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category="Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category="Firing")
	void Fire();

	void AimAt(FVector Location);
	
	EFiringState GetFiringState() const;
protected:
	UPROPERTY(BlueprintReadOnly, Category="State")
	EFiringState FiringState = EFiringState::Locked;

	UPROPERTY(EditAnywhere, Category="Firing")
	float LaunchSpeed = 10000.f;

	UPROPERTY(BlueprintReadOnly, Category="Firing")
	int Ammo = 10;

	UPROPERTY(EditAnywhere, Category="Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Setup")
	double ReloadTimeInSeconds = 3;

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;

	FVector AimDirection;

	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsBarrelMoving();
	void AimBarrel();
};
