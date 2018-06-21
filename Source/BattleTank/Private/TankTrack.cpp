// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UTankTrack::DriveTrack(float AxisValue) const
{
	TArray<ASprungWheel*> Wheels = GetWheels();
	
	UE_LOG(LogTemp, Warning, TEXT("Wheels: %d"), Wheels.Num());

	if (!Wheels.Num())
	{
		return;
	}


	const float ForcePerWheel = AxisValue * TrackMaxDrivingForce / Wheels.Num();

	for (auto Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	for (auto Child : Children)
	{
		auto Wheel = Cast<ASprungWheel>(Child);
		if (Wheel)
		{
			Wheels.Add(Wheel);
		}
	}

	return Wheels;
}
