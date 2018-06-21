// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category="Input")
	void DriveTrack(float AxisValue) const;

private:
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.0f;

	TArray<ASprungWheel*> GetWheels() const;
};