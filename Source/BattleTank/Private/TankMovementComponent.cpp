// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	const auto NormalizedThrow = FMath::Clamp(Throw, -1.f, 1.f);

	LeftTrack->SetThrottle(NormalizedThrow);
	RightTrack->SetThrottle(NormalizedThrow);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	const auto NormalizedThrow = FMath::Clamp(Throw, -1.f, 1.f);

	LeftTrack->SetThrottle(NormalizedThrow);
	RightTrack->SetThrottle(-NormalizedThrow);
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