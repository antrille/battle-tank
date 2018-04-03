// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	const auto NormalizedThrottle = FMath::Clamp(Throttle, -1.f, 1.f);

	auto ForceApplied = GetForwardVector() * NormalizedThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}
