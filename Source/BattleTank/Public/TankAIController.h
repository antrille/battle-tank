// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

#pragma region Forward declarations

class ATank;

#pragma endregion

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void Tick(float DeltaSeconds) override;
	void BeginPlay() override;

private:	

};
