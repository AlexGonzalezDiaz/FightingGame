// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameGameMode.h"
#include "FightingGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFightingGameGameMode::AFightingGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
