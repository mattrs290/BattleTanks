// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"


void UTankTurret::Pivot(float RelativeSpeed)
{
	auto Speed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = Speed * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	//auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}

