// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable, Category = "Tank Settings")
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable, Category = "Tank Settings")
	float GetStartingHealth();

	UPROPERTY(BlueprintAssignable)
	FTankDelegate OnDeath;

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth = 0;
};
