// Fill out your copyright notice in the Description page of Project Settings.


#include "Main/KaijuPVPGameState.h"
#include "Main/Runners/LocalRunner.h"
#include "Gameplay/Actors/FightingGameCharacter.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

void AKaijuPVPGameState::BeginPlay()
{
	Super::BeginPlay();

	// LOCAL RUNNER

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	LocalRunner = GetWorld()->SpawnActor<ALocalRunner>(ALocalRunner::StaticClass(), SpawnParams);

	// CAMERA
	CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
	CameraActor->GetCameraComponent()->SetFieldOfView(54);


	//Need structure to store the locations of the player start ovjects
	FindPlayerStarts();

	////Set up the GameState on the fighting character
	//for (int i = 0; i < MaxPlayerObjects; i++)
	//{
	//	BattleData.MainPlayer[i]->GameState = this;
	//	BattleData.StartLocations[i].Z = Players[i]->PosZ;
	//	Players[i]->GroundLevel = Players[i]->PosZ;
	//}

	//Create an array to hold all the players that are in the game mode.
	//AssignControllers(Players[1]);

}

void AKaijuPVPGameState::Init()
{
	for (int i = 0; i < MaxObjects; i++)
	{
		Players[i] = GetWorld()->SpawnActor<AFightingGameCharacter>(PVP_Data.PlayerList[0], PVP_Data.StartLocations[i], FRotator::ZeroRotator);
		Players[i]->PlayerIndex = i; //Setting player 1 and 2.
	}
	//Filling out the BattleData
	PVP_Data.MainPlayer[0] = Players[0];
	PVP_Data.MainPlayer[1] = Players[1];
}

void AKaijuPVPGameState::FindPlayerStarts()
{
}

void AKaijuPVPGameState::AssignControllers(AFightingGameCharacter* Player, ATrainerCharacter* Trainer)
{
}