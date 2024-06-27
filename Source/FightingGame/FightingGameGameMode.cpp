// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameGameMode.h"
#include "KaijuKolosseumGameState.h"
#include "FightingGameCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "CharacterSelectData.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"


AFightingGameGameMode::AFightingGameGameMode()
{
    // Log a message when the game mode is constructed
    UE_LOG(LogTemp, Log, TEXT("FightingGameGameMode constructor called"));
	
}


void AFightingGameGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay of FightingGameMode"));
    
    //getPlayerStartPoints();
}


