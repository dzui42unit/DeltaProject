// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnnManagerInterface.h"
#include "GameFramework/Character.h"
#include "SpawnManagerBase.generated.h"

UCLASS()
class DELTAGAME_API ASpawnManagerBase : public AActor, public ISpawnnManagerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManagerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Pool of spawned Actors
	UPROPERTY()
	TArray<ACharacter*> ActorsPool;
	// Actor to spawn for this manager, could be made an array for multiple types at once to spawns
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> SpawnActor;
	// actor spawn params (collision handling f.e.)
	FActorSpawnParameters ActorSpawnParameters;
	// pool size of actors
	int32 PoolSize;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	
	// Begin ISpawnManagerInterface
	virtual ACharacter* SpawnCharacter(const FVector& SpawnLocation);
	virtual FVector CalculateSpawnPoint() override { return FVector::ZeroVector; }
	virtual TArray<ACharacter*>	GetActorsPool() { return ActorsPool; }
	virtual void SpawnWave() { }
	virtual int32 GetPoolSize() const override { return PoolSize; }
	// End ISpawnManagerInterface
};
