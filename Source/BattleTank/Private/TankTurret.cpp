// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankTurret::Rotate(FRotator Rotation)
{
	auto ParentRotation = FRotator(0, GetOwner()->GetActorRotation().Yaw, 0);
	
	/*
	const auto RotationStep = FMath::RInterpConstantTo(
		FRotator(0, GetComponentRotation().Yaw, 0),
		Rotation,
		GetWorld()->DeltaTimeSeconds, 
		MaxDegreesPerSecond
	);*/


	SetRelativeRotation(Rotation - ParentRotation);
}
