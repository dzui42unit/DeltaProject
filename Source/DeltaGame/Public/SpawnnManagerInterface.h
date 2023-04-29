// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpawnnManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpawnnManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DELTAGAME_API ISpawnnManagerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual ACharacter* SpawnCharacter(const FVector& SpawnLocation) { return nullptr; };
	virtual FVector CalculateSpawnPoint() { return FVector::ZeroVector; };

};
