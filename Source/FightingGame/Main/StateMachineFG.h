#pragma once

#include "CoreMinimal.h"
#include "StateData.h"
#include "Containers/Map.h"
#include "StateMachineFG.generated.h"

class UState;
class AFightingGameCharacter;

USTRUCT()
struct FStateInfo
{
	GENERATED_BODY()

	UState* State;
	EStateFlags StateType;
	EStateFlags StanceReq;
	EStateFlags ExitType;

	FStateInfo()
		: State(nullptr)
		, StateType(EStateFlags::None)
		, StanceReq(EStateFlags::None)
		, ExitType(EStateFlags::None)
	{}

	FStateInfo(UState* InState, EStateFlags InStateType, EStateFlags InStanceReq, EStateFlags InExitType)
		: State(InState)
		, StateType(InStateType)
		, StanceReq(InStanceReq)
		, ExitType(InExitType)
	{}

};

USTRUCT(BlueprintType)
struct FIGHTINGGAME_API FStateMachineFG
{
	GENERATED_BODY()

public:	
	void Update(int Inputs);
	void SetState(EStateFlags NewState);
	void LoadStates(UObject* Outer, UStateData* DA);

	UPROPERTY()
	AFightingGameCharacter* Parent;

	//Current CharacterState, made it EditAnywhere so I can watch in Editor
	UPROPERTY(EditAnywhere)
	EStateFlags CurrState;

	//Used to know when a state has started and to continuosly check when the state will exit.
	bool StateComplete = false;
	bool StateStarted = false;

protected:

	TArray<FStateInfo> StateInfos;

private:

	//Access the DataAsset containing CommmonStates
	UStateData* StatesArray;
	//Multimap used in Update(), Key = PlayerInput. 
	TMultiMap<int32, FStateInfo> StateMap;

};
