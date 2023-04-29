// Fill out your copyright notice in the Description page of Project Settings.


#include "CircleSpawnManager.h"
#include "DrawDebugHelpers.h"


ACircleSpawnManager::ACircleSpawnManager()
{
	// set default values
	CircleSpawnParameters.CircleRadius = 800.f;
	CircleSpawnParameters.SectorStep = 10;
}

void ACircleSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	// reserve an array of actors pool
	PoolSize = CIRCLE_DEG / static_cast<int32>(CircleSpawnParameters.SectorStep);
	ActorsPool.Reserve(PoolSize);
	// start spawning process
	SpawnWave();
}

FVector ACircleSpawnManager::CalculateSpawnPoint()
{
	return FVector::ZeroVector;
}

void ACircleSpawnManager::SpawnWave()
{
	FVector CircleCenter = GetActorLocation();

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Fatal, TEXT("World is not valid"))
		return;
	}

	#if WITH_EDITOR
	DrawDebugSphere(World, CircleCenter, 50.f, 100, FColor::Green, true);
	#endif

	for (int32 i = 0; i < PoolSize; ++i)
	{
		// calculate the forward vector and rotate it on i * angle rotation of the  sector steps
		FVector ForwardVector = GetActorForwardVector();
		const FRotator Rotator(0, i * CircleSpawnParameters.SectorStep, 0);
		ForwardVector = Rotator.RotateVector(ForwardVector);
		// calculate the spawn point location
		FVector SpawnPointLocation = ForwardVector * CircleSpawnParameters.CircleRadius + CircleCenter;
		
		#if WITH_EDITOR
		DrawDebugLine(World, CircleCenter, SpawnPointLocation, FColor::Cyan, true, 10.f);
		DrawDebugSphere(World, SpawnPointLocation, 50.f, 5, FColor::Cyan, true, 10.f);
		#endif
		// spawn character at location
		if (ACharacter* SpawnedCharacter = SpawnCharacter(SpawnPointLocation))
		{
			ActorsPool.Add(SpawnedCharacter);
		}
	}
}


