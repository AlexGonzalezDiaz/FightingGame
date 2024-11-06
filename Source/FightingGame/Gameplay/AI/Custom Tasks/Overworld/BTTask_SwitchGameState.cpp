// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/Custom Tasks/Overworld/BTTask_SwitchGameState.h"
#include "Main/KaijuKolosseumGameState.h"

UBTTask_SwitchGameState::UBTTask_SwitchGameState(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Switch Game State";
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_SwitchGameState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const GameState = Cast<AKaijuKolosseumGameState>(GetWorld()->GetGameState()))
	{
		GameState->SetGameState(EGameState::Battle);
		GameState->UpdateCamera(EGameState::Battle, nullptr);
	}
	return EBTNodeResult::Succeeded;
}
