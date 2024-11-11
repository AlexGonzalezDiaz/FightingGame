// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KaijuPVPGameState.generated.h"

class AFightingGameCharacter;
class ATrainerCharacter;
class ALocalRunner;
class UCameraActor;
/**
 * 
 */
UCLASS()
class FIGHTINGGAME_API AKaijuPVPGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	//Run in frames
	ALocalRunner* LocalRunner;
	ACameraActor* CameraActor;

	virtual void BeginPlay() override;
	void Init();
	void FindPlayerStarts();
	void AssignControllers(AFightingGameCharacter* Player, ATrainerCharacter* Trainer);
};
