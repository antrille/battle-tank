// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category="Input")
	void SetThrottle(float Throttle);

private:
	// Max force per tracks in newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f; // 40 tonne tank, 1g acceleration
};
