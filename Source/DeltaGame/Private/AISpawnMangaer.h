// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "SpawnnManagerInterface.h"
#include "AISpawnMangaer.generated.h"

USTRUCT(BlueprintType)
struct FGridSpawnerParameters
{
	GENERATED_USTRUCT_BODY()

	// Actor to spawn for this manager, could be made an array for multiple types at once to spawns
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> SpawnActor;
	// actor spawn params (collision handling f.e.)
	FActorSpawnParameters ActorSpawnParams;
	// Grid SizeX 
	UPROPERTY(EditAnywhere, meta = (ClampMin = 2, ClampMax = 20))
	int32 GridSizeX;
	// Grind SizeY the grid will be X * Y
	UPROPERTY(EditAnywhere, meta = (ClampMin = 2, ClampMax = 20))
	int32 GridSizeY;
	// Distance between actors to spawn
	UPROPERTY(EditAnywhere, meta = (ClampMin = 50.f, ClampMax = 600.f))
	float DistanceSpawnStep;
};

UCLASS()
class AAISpawnMangaer : public AActor, public ISpawnnManagerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawnMangaer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// spawn parameters
	UPROPERTY(EditAnywhere)
	FGridSpawnerParameters GridSpawnerParameters;
	// Pool of spawned Actors
	UPROPERTY()
	TArray<ACharacter*> ActorsPool;
	// spawn on grid
	void SpawnOnGrid();
	// Whether to test grid spawner of radial
	UPROPERTY(EditAnywhere)
	bool bStwitchSpawnMode;

	// Begin ISpawnnManagerInterface
	ACharacter* SpawnCharacter(const FVector& SpawnLocation) override;
	// End ISpawnnManagerInterface

	void SpawnOnCircle();

	UPROPERTY(EditAnywhere)
	float CircleRadius;

	UPROPERTY(EditAnywhere)
	float SectorStep;
};
