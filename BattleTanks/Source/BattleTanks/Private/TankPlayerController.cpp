// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Containers/UnrealString.h"
#include "Math/Vector2D.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s "), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *OutHitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D((ViewportSizeX * CrossHairXlocation), (ViewportSizeY * CrossHairYLocation));

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		(GetLookVectorHitLocation(LookDirection, OutHitLocation));
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
	{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult OutHit;
	auto Start = PlayerCameraManager->GetCameraLocation();
	float Reach = 1000000.f;
	FVector EndTrace = Start + (LookDirection * Reach);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, EndTrace, ECC_Visibility))
	{
		OutHitLocation = OutHit.Location;
		return true;
	}
	return false;
}