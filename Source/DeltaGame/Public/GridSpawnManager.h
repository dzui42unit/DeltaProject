// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnManagerBase.h"
#include "GridSpawnManager.generated.h"

// structure that will hold specific for the grid spawner data
USTRUCT(BlueprintType)
struct FGridSpawnerParameters
{
	GENERATED_USTRUCT_BODY()

	// Grid SizeX 
	UPROPERTY(EditAnywhere, meta = (ClampMin = 2, ClampMax = 20))
	int32 GridSizeX;
	// Grind SizeY the grid will be X * Y
	UPROPERTY(EditAnywhere, meta = (ClampMin = 2, ClampMax = 20))
	int32 GridSizeY;
	// Distance between actors to spawn
	UPROPERTY(EditAnywhere, meta = (ClampMin = 200.f, ClampMax = 1000.f))
	float DistanceSpawnStep;
};


UCLASS()
class DELTAGAME_API AGridSpawnManager : public ASpawnManagerBase
{
	GENERATED_BODY()

public:

	AGridSpawnManager();

	FGridSpawnerParameters& GetSpawnerParameters() { return GridSpawnParameters; }

	// Begin ISpawnManagerInterface
	virtual FVector CalculateSpawnPoint() override;
	virtual void SpawnWave();
	// End ISpawnManagerInterface

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// parameters for grid spawner
	UPROPERTY(EditAnywhere)
	FGridSpawnerParameters GridSpawnParameters;
};
