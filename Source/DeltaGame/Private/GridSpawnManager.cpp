// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSpawnManager.h"

AGridSpawnManager::AGridSpawnManager()
{
	// set default values for spawner
	GridSpawnParameters.GridSizeX = 5;
	GridSpawnParameters.GridSizeY = 5;
	GridSpawnParameters.DistanceSpawnStep = 300.f;
}

void AGridSpawnManager::BeginPlay()
{
	Super::BeginPlay();

	// reserve an array of actors pool
	PoolSize = GridSpawnParameters.GridSizeX * GridSpawnParameters.GridSizeY;
	ActorsPool.Reserve(PoolSize);
	// start spawning process
	SpawnWave();
}

FVector AGridSpawnManager::CalculateSpawnPoint()
{
	return FVector::ZeroVector;
}

// implements logic for spawning a wave on a grid size N * M 
void AGridSpawnManager::SpawnWave()
{
	// starting location of actors to spawn, it is an actor location for now
	const FVector& StartLocation = GetActorLocation();
	FVector CurrentSpawnLocation = StartLocation;

	// perform actors spawn
	for (int32 i = 0; i < PoolSize; ++i)
	{
		if (auto* SpawnedCharacter = SpawnCharacter(CurrentSpawnLocation))
		{
			// add actor to the pool
			ActorsPool.Add(SpawnedCharacter);
			// check if we have filled the row and are going to exceed number of columns
			// recalculate starting point so it start on a new row
			if ((i % GridSpawnParameters.GridSizeY) == (GridSpawnParameters.GridSizeY - 1))
			{
				CurrentSpawnLocation.X = StartLocation.X + GridSpawnParameters.DistanceSpawnStep * ((i + 1) / GridSpawnParameters.GridSizeY);
				CurrentSpawnLocation.Y = StartLocation.Y;
			}
			// simply move along Y axis and spawn a new one there
			else
			{
				CurrentSpawnLocation.Y += GridSpawnParameters.DistanceSpawnStep;
			}
		}
	}
}
