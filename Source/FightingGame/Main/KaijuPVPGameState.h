// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KaijuPVPGameState.generated.h"

class AFightingGameCharacter;
class ATrainerCharacter;
class ALocalRunner;
class UCameraActor;
constexpr int32 MaxObjects = 2;
//constexpr float OneFrame = 0.0166666666;

USTRUCT(BlueprintType)
struct FPvPBattleData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AFightingGameCharacter>> PlayerList;

	UPROPERTY()
	AFightingGameCharacter* MainPlayer[2];

	UPROPERTY(EditAnywhere)
	FVector StartLocations[2];

	TArray <AActor*> playerStartPoints;

};


UCLASS()
class FIGHTINGGAME_API AKaijuPVPGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BluePrintReadWrite, EditAnywhere)
	FPvPBattleData PVP_Data;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform BattlePlayerTransform;

protected:

	UPROPERTY()
	AFightingGameCharacter* Players[MaxObjects]{};

	//Run in frames
	ALocalRunner* LocalRunner;
	ACameraActor* CameraActor;

	virtual void BeginPlay() override;
	void Init();
	void FindPlayerStarts();
	void AssignControllers(AFightingGameCharacter* Player, ATrainerCharacter* Trainer);
};
