// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Main/StateData.h"
#include "Main/StateMachineFG.h"
#include "FightingGameGameMode.h"
#include "KaijuKolosseumGameState.generated.h"

class AFightingGameCharacter;
class ATrainerCharacter;
class AAICharacter;
class AKaijuPlayerController;
class ATrainerController;
constexpr int32 MaxPlayerObjects = 2;
constexpr float OneFrame = 0.0166666666;

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

	UPROPERTY(EditAnywhere)
	FVector StartLocations[2];

	TArray <AActor*> playerStartPoints;

};

USTRUCT(BlueprintType)
struct FRPGData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ATrainerCharacter> TrainerBP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AAICharacter> WKaijuBP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATrainerCharacter* Trainer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AFightingGameCharacter* PartnerKaiju;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AAICharacter* WKaiju;

	//Variable for previous save spot starting location

};

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Overworld,
	Battle
};


UCLASS()
class FIGHTINGGAME_API AKaijuKolosseumGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	//Sets default values for the this actors properties
	AKaijuKolosseumGameState();

	/*---- CONTROLLERS ---*/
	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	TSubclassOf<AKaijuPlayerController> PlayerControllerClass;

	UPROPERTY(EditDefaultsOnly,Category = "Controllers")
	TSubclassOf<ATrainerController> TrainerControllerClass;
	/*---- CONTROLLERS ---*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBattleState BattleState = FBattleState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACameraActor* CameraActor = nullptr;

	UPROPERTY(BluePrintReadWrite, EditAnywhere)
	FRPGData RPGData;

	UPROPERTY(BluePrintReadWrite, EditAnywhere)
	FBattleData BattleData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform BattlePlayerTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	EGameState CurrentGameState;

	//Reading Inputs from the controller
	int GetLocalInputs(int Index) const;

	FStateMachineFG StateMachine;

	//Sets the inputs from the player controller to the players
	void UpdateState(int32 P1Inputs, int32 P2Inputs);
	//Calling this function from the Local Runner
	void UpdateState();

	void SetGameState(EGameState NewState);

	void UpdateCamera(EGameState CurrState, ATrainerCharacter* Player);
	EGameState GetGameState();

	//Spawning the AI characters randomly on the map. 
	UPROPERTY(EditDefaultsOnly, Category = "AI Spawning")
	float SpawnRadius = 1000.0f;

	void SpawnAIKaiju();

	void SpawnPartner(int Distance);

protected:

	UPROPERTY()
	AFightingGameCharacter* Players[MaxPlayerObjects] {};

	UPROPERTY()
	ATrainerCharacter* RPGPlayer;

	UPROPERTY()
	class ALocalRunner* LocalRunner = nullptr;

	UFUNCTION(BlueprintCallable)
	void AssignControllers(AFightingGameCharacter* Player, ATrainerCharacter* Trainer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	//Spawns the characters and sets the BattleInfo player arrays. 
	void Init(); 
	//Set the players from the player list to be the main characters. 
	//Finds the PlayerStarts so we can use their location.
	void FindPlayerStarts();

private:
	int32 PlayerIndex = 0;

	
};
