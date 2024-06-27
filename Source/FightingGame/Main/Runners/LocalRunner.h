// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocalRunner.generated.h"

class AFightingGameCharacter;
class AFStateMachineFG;
class AKaijuKolosseumGameState;

UCLASS()
class FIGHTINGGAME_API ALocalRunner : public AActor
{
	GENERATED_BODY()
	
protected:


public:	
	ALocalRunner();
	// Called every frame

	UPROPERTY(EditAnywhere, Category = "Fixed Update")
	int32 FixedTimeStep = 16;

	virtual void Tick(float DeltaTime) override;

private:

	void FixedUpdate();
	int32 AccumulatedTime;

	//Fixed time step required to optimize sending payloads in general.
	static const int32 FIXED_TIME_STEPS_MS = 16;

};
