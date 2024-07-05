#pragma once

#include "CoreMinimal.h"
#include "StateData.h"
#include "StateMachineFG.generated.h"

class UState;
class AFightingGameCharacter;

USTRUCT()
struct FGameStateMachine
{
	GENERATED_BODY()
	//A reference to the current state
	UPROPERTY()
	//An array of names corresponding to each state used for lookup
	TArray<FName> StateNames;
	//Input that is needed to enter the state.
	TArray<int> InputReq;
	//Current CharacterState
	EStateFlags CurrentState;
	//The type of state that the state BP is.
	TArray<EStateFlags> StateType;
	//Required to enter the next state
	TArray<EStateFlags> StanceReq;
	//Default Exit state.
	TArray<EStateFlags> ExitType;
	//An Array of all available current states
	TArray<UState*> States;
		
};

USTRUCT(BlueprintType)
struct FIGHTINGGAME_API FStateMachineFG
{
	GENERATED_BODY()

public:
	EStateFlags GetStateNames();	
	void Update(int Inputs);
	void SetState(EStateFlags NewState);
	void Initialize();
	void LoadStates(UObject* Outer, UStateData* DA);

	UPROPERTY()
	AFightingGameCharacter* Parent;

	UPROPERTY(VisibleAnywhere)
	bool StateComplete = false;
	bool StateStarted = false;

protected:
	int32 Index = 0;
	

private:
	UPROPERTY(Transient)
	UStateData* StatesArray;

	UPROPERTY(VisibleAnywhere)
	FGameStateMachine KaijuSM;

};
