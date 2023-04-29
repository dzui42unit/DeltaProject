// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeltaGameGameMode.h"
#include "DeltaGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADeltaGameGameMode::ADeltaGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
