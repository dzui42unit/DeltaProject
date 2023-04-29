// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManagerBase.h"

// Sets default values
ASpawnManagerBase::ASpawnManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// we want always to spawn actors, event if some collision takes place
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// default pool size
	PoolSize = 0;
}

// Called when the game starts or when spawned
void ASpawnManagerBase::BeginPlay()
{
	Super::BeginPlay();

	check(IsValid(SpawnActor));
}

// Called every frame
void ASpawnManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ACharacter* ASpawnManagerBase::SpawnCharacter(const FVector& SpawnLocation)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Fatal, TEXT("World is not valid"))
		return nullptr;
	}

	return  World->SpawnActor<ACharacter>(SpawnActor, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);
}

