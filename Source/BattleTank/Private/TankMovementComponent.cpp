// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet))
	{
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}

	const auto NormalizedAxisValue = FMath::Clamp(Throw, -1.f, 1.f);

	LeftTrack->DriveTrack(NormalizedAxisValue);
	RightTrack->DriveTrack(NormalizedAxisValue);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}
	
	const auto NormalizedAxisValue = FMath::Clamp(Throw, -1.f, 1.f);

	LeftTrack->DriveTrack(NormalizedAxisValue);
	RightTrack->DriveTrack(-NormalizedAxisValue);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	const auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal(); 
	const auto NormalizedVelocity = MoveVelocity.GetSafeNormal();

	const auto DotProduct = FVector::DotProduct(TankForwardVector, NormalizedVelocity);
	IntendMoveForward(DotProduct);

	const auto CrossProduct = FVector::CrossProduct(TankForwardVector, NormalizedVelocity);
	IntendTurnRight(CrossProduct.Z);
}