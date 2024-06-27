#include "Main/StateMachineFG.h"
#include "FightingGameCharacter.h"
#include "State.h"
#include "Engine/Engine.h"


FName FStateMachineFG::GetStateNames()
{
	//FGStateMachine->StateNames
	return {};
}

void FStateMachineFG::Update(int Inputs)
{
	if (Inputs != 0)
	{
		if (KaijuSM.States.Num() != NULL)
		{
			for (int i = 0; i < KaijuSM.States.Num(); i++)
			{
				if (KaijuSM.InputReq[i] == Inputs)
				{
					KaijuSM.CurrentState = KaijuSM.States[i];
					KaijuSM.States[i]->Parent = Parent;
					KaijuSM.States[i]->Execute_Implementation();
				}
			}

		}

	}
}

void FStateMachineFG::SetState()
{
	//Set Current state
}

void FStateMachineFG::Initialize()
{
	//Set the defualt state of the character to idle if no inputs are recieved.

}

void FStateMachineFG::LoadStates(UObject* Outer, UStateData* DA)
{
	KaijuSM.CurrentState = nullptr;
	if (DA)
	{
		StatesArray = DA;

		for (const FStateDataStruct& StateData : StatesArray->StateDataStruct)
		{
			if (StateData.StateInfo)
			{
				UState* LoadedObj = NewObject<UState>(Outer, StateData.StateInfo);
				if (LoadedObj)
				{
					FName NewName = StateData.StateName;
					int InputFlag = StateData.InputFlag;

					UE_LOG(LogTemp, Log, TEXT("Found valid state"));
					//LoadedObj->Parent
					KaijuSM.States.Add(LoadedObj);
					KaijuSM.StateNames.Add(NewName);
					KaijuSM.InputReq.Add(InputFlag);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to create state object"));
				}
			}
		}
	}
}
