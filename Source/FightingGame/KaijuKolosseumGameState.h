// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Main/StateData.h"
#include "Main/StateMachineFG.h"
#include "FightingGameGameMode.h"
#include "KaijuKolosseumGameState.generated.h"

/**
 * 
 */
class AFightingGameCharacter;
constexpr int32 MaxPlayerObjects = 2;

USTRUCT(BlueprintType)
struct FBattleState
{
	GENERATED_BODY()

	FVector CameraPosition = FVector();
};

USTRUCT(BlueprintType)
struct FBattleData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AFightingGameCharacter>> PlayerList;

	UPROPERTY()
	AFightingGameCharacter* MainPlayer[2];

	TArray <AActor*> playerStartPoints;

	FVector StartLocations[2];

};

UCLASS()
class FIGHTINGGAME_API AKaijuKolosseumGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	//Sets default values for the this actors properties
	AKaijuKolosseumGameState();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBattleState BattleState = FBattleState();

	UPROPERTY(BlueprintReadWrite)
	ACameraActor* CameraActor = nullptr;

	UPROPERTY(BluePrintReadWrite, EditAnywhere)
	FBattleData BattleData;

	//Reading Inputs from the controller
	int GetLocalInputs(int Index) const;

protected:

	UPROPERTY()
	AFightingGameCharacter* Players[MaxPlayerObjects] {};

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	//Spawns the characters and sets the BattleInfo player arrays. 
	void Init(); 
	//Set the players from the player list to be the main characters. 
	//Finds the PlayerStarts so we can use their location.
	void FindPlayerStarts();
	//Sets the inputs from the player controller to the players
	void UpdateState(int32 P1Inputs, int32 P2Inputs);

private:
};
