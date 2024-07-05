// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocalRunner.generated.h"


UCLASS()
class FIGHTINGGAME_API ALocalRunner : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	float CurrTime = 0;

public:	
	ALocalRunner();
	// Called every frame

	UPROPERTY(EditAnywhere, Category = "Fixed Update")
	int32 FixedTimeStep = 16;
	void FixedUpdate(float DeltaTime);

private:

	UPROPERTY()
	class AKaijuKolosseumGameState* InState;
};
