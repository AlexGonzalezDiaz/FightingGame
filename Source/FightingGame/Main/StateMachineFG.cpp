#include "Main/StateMachineFG.h"
#include "FightingGameCharacter.h"
#include "State.h"
#include "Engine/Engine.h"


EStateFlags FStateMachineFG::GetStateNames()
{
	return KaijuSM.CurrentState;
}

void FStateMachineFG::Update(int Inputs)
{
	if (KaijuSM.States.Num() != NULL)
	{
		for (int i = 0; i < KaijuSM.States.Num(); i++)
		{
			if (KaijuSM.InputReq[i] == Inputs && KaijuSM.CurrentState == KaijuSM.StanceReq[i])
			{
				Index = i;
				KaijuSM.States[i]->Parent = Parent;
				KaijuSM.States[i]->Execute_Implementation();
				StateStarted = KaijuSM.States[i]->InitState; // Change InitState to true in ExecuteImplementation
				SetState(KaijuSM.StateType[i]);
			}		
		}

		if (StateStarted)
		{
			StateComplete = KaijuSM.States[Index]->ExitState_Implementation(); // Change InitState to False
			if (StateComplete)
			{   
				SetState(KaijuSM.ExitType[Index]);
			}
		}

	}
}

void FStateMachineFG::SetState(EStateFlags NewState)
{
	//Set Current state
	KaijuSM.CurrentState = NewState;
}

void FStateMachineFG::Initialize()
{
	//Set the defualt state of the character to idle if no inputs are recieved.

}

void FStateMachineFG::LoadStates(UObject* Outer, UStateData* DA)
{
	SetState(EStateFlags::Idle);

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
					EStateFlags Type = StateData.StateType;
					EStateFlags ReqState = StateData.EntryStateType;
					EStateFlags ExitState = StateData.ExitStateType;

					KaijuSM.StateNames.Add(NewName);
					KaijuSM.InputReq.Add(InputFlag);
					KaijuSM.StateType.Add(Type);
					KaijuSM.StanceReq.Add(ReqState);
					KaijuSM.ExitType.Add(ExitState);
					KaijuSM.States.Add(LoadedObj);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to create state object"));
				}
			}
		}
	}
}
