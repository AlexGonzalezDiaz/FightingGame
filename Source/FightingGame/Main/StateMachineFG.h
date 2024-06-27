#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "StateData.h"
#include "StateMachineFG.generated.h"

class AFightingGameCharacter;

USTRUCT(BlueprintType)
struct FGameStateMachine
{
	GENERATED_BODY()
	//A reference to the current state
	UPROPERTY()
	UState* CurrentState;
	//An Array of all available current states
	TArray<UState*> States;
	//An array of names corresponding to each state used for lookup
	TArray<FName> StateNames;
	//Input that is needed to enter the state.
	TArray<int> InputReq;
};

USTRUCT()
struct FIGHTINGGAME_API FStateMachineFG
{
	GENERATED_BODY()

public:
	FName GetStateNames();	
	void Update(int Inputs);
	void SetState();
	void Initialize();
	void LoadStates(UObject* Outer, UStateData* DA);

	UPROPERTY()
	AFightingGameCharacter* Parent;

protected:
	

private:
	UPROPERTY(Transient)
	UStateData* StatesArray;

	UPROPERTY()
	FGameStateMachine KaijuSM;

};
