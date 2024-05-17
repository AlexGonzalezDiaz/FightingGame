// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KaijuKolosseumState.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBattleState
{
	GENERATED_BODY()

	FVector CameraPosition = FVector();
};

UCLASS()
class FIGHTINGGAME_API AKaijuKolosseumState : public AGameStateBase
{
	GENERATED_BODY()

public:
	//Sets default values for the this actors properties
	AKaijuKolosseumState();

	UPROPERTY(BlueprintReadWrite)
	FTransform BattleSceneTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBattleState BattleState = FBattleState();

	UPROPERTY(BlueprintReadWrite)
	ACameraActor* CameraActor = nullptr;

protected:
	virtual void BeginPlay() override;
	
};
