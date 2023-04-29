// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnManagerBase.h"
#include "CircleSpawnManager.generated.h"

#define CIRCLE_DEG 360

// structure that will hold specific for the grid spawner data
USTRUCT(BlueprintType)
struct FCircleSpawnerParameters
{
	GENERATED_USTRUCT_BODY()

	// spawn circle radius
	UPROPERTY(EditAnywhere, meta = (ClampMin = 600.f, ClampMax = 2500.f))
	float CircleRadius;
	// substep to spawn with (in degrees)
	UPROPERTY(EditAnywhere, meta = (ClampMin = 10, ClampMax = 180, Delta = 5))
	int32 SectorStep;
};

UCLASS()
class DELTAGAME_API ACircleSpawnManager : public ASpawnManagerBase
{
	GENERATED_BODY()
	
public:
	ACircleSpawnManager();

	FCircleSpawnerParameters& GetSpawnerParameters() { return CircleSpawnParameters; }

	// Begin ISpawnManagerInterface
	virtual FVector CalculateSpawnPoint() override;
	virtual void SpawnWave();
	// End ISpawnManagerInterface

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// parameters for circulars spawner
	UPROPERTY(EditAnywhere)
	FCircleSpawnerParameters CircleSpawnParameters;

};
