// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"


void UTankTurret::Pivot(float RelativeSpeed)
{
	auto Speed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto DirectionChange = Speed * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto NewDirection = RelativeRotation.Yaw + DirectionChange;

	SetRelativeRotation(FRotator(0, NewDirection, 0));
}

