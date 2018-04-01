// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankBarrel::Elevate(FRotator Rotation)
{
	//const auto RotationStep = FMath::RInterpConstantTo(
	//	FRotator(GetComponentRotation().Pitch, 0, 0),
	//	Rotation,
	//	GetWorld()->DeltaTimeSeconds,
	//	MaxDegreesPerSecond
	//);

	auto ParentRotation = FRotator(GetOwner()->GetActorRotation().Pitch, 0, 0);
	auto ResultRotation = Rotation - ParentRotation;
	ResultRotation.Pitch = FMath::ClampAngle(ResultRotation.Pitch, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(ResultRotation);
}
