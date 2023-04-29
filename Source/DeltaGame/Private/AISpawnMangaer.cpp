// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnMangaer.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAISpawnMangaer::AAISpawnMangaer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set default values for spawner
	GridSpawnerParameters.GridSizeX = 5;
	GridSpawnerParameters.GridSizeY = 5;
	GridSpawnerParameters.DistanceSpawnStep = 75.f;
	GridSpawnerParameters.ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// apply grid spawn mode by default
	bStwitchSpawnMode = false;

	CircleRadius = 800.f;
	SectorStep = 90.f;
}

// Called when the game starts or when spawned
void AAISpawnMangaer::BeginPlay()
{
	Super::BeginPlay();

	check(IsValid(GridSpawnerParameters.SpawnActor));

	// spawn on grid actors
	if (!bStwitchSpawnMode)
	{
		SpawnOnGrid();
	}
	else
	{
		// radial spawner logic
		SpawnOnCircle();
	}
}

// Called every frame
void AAISpawnMangaer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACharacter* AAISpawnMangaer::SpawnCharacter(const FVector& SpawnLocation)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Fatal, TEXT("World is not valid"))
		return nullptr;
	}

	return  World->SpawnActor<ACharacter>(GridSpawnerParameters.SpawnActor, SpawnLocation, FRotator::ZeroRotator, GridSpawnerParameters.ActorSpawnParams);
}

void AAISpawnMangaer::SpawnOnCircle()
{
	FVector CircleCenter = GetActorLocation();

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Fatal, TEXT("World is not valid"))
		return;
	}

	DrawDebugSphere(World, CircleCenter, 50.f, 100, FColor::Green, true);

	int32 Iterations = 360 / static_cast<int32>(SectorStep);

	for (int32 i = 0; i < Iterations; ++i)
	{
		FVector ForwardVector = GetActorForwardVector();
		const FRotator Rotator(0, i * SectorStep, 0);
		ForwardVector = Rotator.RotateVector(ForwardVector);

		FVector SpawnPointLocation = ForwardVector * CircleRadius + CircleCenter;

		DrawDebugLine(World, CircleCenter, SpawnPointLocation, FColor::Cyan, true, 10.f);
		DrawDebugSphere(World, SpawnPointLocation, 50.f, 5, FColor::Cyan, true, 10.f);

		SpawnCharacter(SpawnPointLocation);
	}

}

void AAISpawnMangaer::SpawnOnGrid()
{
	// reserve an array of actors pool
	const int32 PoolSize = GridSpawnerParameters.GridSizeX * GridSpawnerParameters.GridSizeY;
	ActorsPool.Reserve(PoolSize);

	// starting location of actors to spawn
	const FVector& StartLocation = GetActorLocation();
	FVector CurrentSpawnLocation = StartLocation;

	// perform actors spawn
	for (int32 i = 0; i < PoolSize; ++i)
	{
		if (auto* SpawnedCharacter = SpawnCharacter(CurrentSpawnLocation))
		{
			ActorsPool.Add(SpawnedCharacter);

			if ((i % GridSpawnerParameters.GridSizeY) == (GridSpawnerParameters.GridSizeY - 1))
			{
				CurrentSpawnLocation.X = StartLocation.X + GridSpawnerParameters.DistanceSpawnStep * ((i + 1) / GridSpawnerParameters.GridSizeY);
				CurrentSpawnLocation.Y = StartLocation.Y;
			}
			else
			{
				CurrentSpawnLocation.Y += GridSpawnerParameters.DistanceSpawnStep;
			}
		}
	}
}

