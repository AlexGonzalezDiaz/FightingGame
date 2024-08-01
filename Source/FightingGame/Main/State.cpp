#include "Main/State.h"
#include "Gameplay/Actors/FightingGameCharacter.h"

void UState::Execute_Implementation() //Used for default implementation for Unreal engine to understand
{
	//InitState = true;
}

bool UState::ExitState_Implementation()
{
	return true;
}

void UState::GetName()
{
}
