#include "Main/State.h"
#include "Gameplay/Actors/FightingGameCharacter.h"

void UState::Execute_Implementation()
{
	Execute();
}

bool UState::ExitState_Implementation()
{
	return ExitState();
}

void UState::GetName()
{
}
