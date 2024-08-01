#include "Main/StateMachineFG.h"
#include "Gameplay/Actors/FightingGameCharacter.h"
#include "State.h"
#include "Engine/Engine.h"


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
					int32 InputFlag = StateData.InputFlag;
					FStateInfo StateInfo(LoadedObj ,StateData.StateType, StateData.EntryStateType, StateData.ExitStateType);
					StateMap.Add(InputFlag, StateInfo);
				}
			}
		}
	}
}

void FStateMachineFG::Update(int Inputs)
{

	if ((StateMap.Num() > 0 && Inputs != 0 ))
	{

		if (!StateStarted)
		{
			StateInfos.Reset();
			StateMap.MultiFind(Inputs, StateInfos);
			for (const FStateInfo& StateInfo : StateInfos)
			{
				if (CurrState == StateInfo.StanceReq)
				{
					StateInfo.State->Parent = Parent;
					StateInfo.State->Execute();
					StateStarted = StateInfo.State->InitState;
					SetState(StateInfo.StateType);
					break;
				}
			}
		}
	}

	if (StateStarted && !StateInfos.IsEmpty())
	{
		FStateInfo& CurrentStateInfo = StateInfos[0];

		if (CurrentStateInfo.State)
		{
			StateComplete = CurrentStateInfo.State->ExitState();
			if (StateComplete)
			{
				SetState(CurrentStateInfo.ExitType);
				StateStarted = false;
				StateComplete = false;
			}
		}
	}
}


void FStateMachineFG::SetState(EStateFlags NewState)
{
	//Set Current state
	CurrState = NewState;
}

void FStateMachineFG::Initialize()
{
	//Set the defualt state of the character to idle if no inputs are recieved.

}


