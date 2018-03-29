// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), HideCategories = ("Collision", "Physics", "Lighting") )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category=Setup)
	float MaxDegreesPerSecond = 5.f;

	UPROPERTY(EditAnywhere, Category=Setup)
	float MaxElevationDegrees = 40.f;

	UPROPERTY(EditAnywhere, Category=Setup)
	float MinElevationDegrees = 0.f;
};
