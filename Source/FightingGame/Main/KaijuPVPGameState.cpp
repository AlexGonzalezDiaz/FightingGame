// Fill out your copyright notice in the Description page of Project Settings.


#include "Main/KaijuPVPGameState.h"
#include "Main/Runners/LocalRunner.h"
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
}

void AKaijuPVPGameState::FindPlayerStarts()
{
}

void AKaijuPVPGameState::AssignControllers(AFightingGameCharacter* Player, ATrainerCharacter* Trainer)
{
}