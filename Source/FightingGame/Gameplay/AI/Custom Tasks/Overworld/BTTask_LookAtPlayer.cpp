// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/Custom Tasks/Overworld/BTTask_LookAtPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Main/KaijuKolosseumGameState.h"
#include "Gameplay/Controllers/KaijuAIController.h"
#include "Kismet/KismetMathLibrary.h"

//Constructor and with node name

//Get AI controller and the npc
//Get the AI characters current location
//Get the trainer characters current location
//Look at rotation. 

UBTTask_LookAtPlayer::UBTTask_LookAtPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Lock onto player";
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_LookAtPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	////Get AI controller and its npc. 
	//if (auto* const controller = Cast<AKaijuAIController>(OwnerComp.GetAIOwner()))
	//{
	//	if (auto* const npc = controller->GetPawn())
	//	{
	//		//Obtain npc location to use as an origin
	//		auto const Origin = npc->GetActorLocation();

	//		AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

	//		auto const TrainerLoc = Player->GetActorLocation();

	//		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Origin, TrainerLoc);

	//		npc->SetActorRotation(LookAtRotation);

	//		return EBTNodeResult::Succeeded;
	//	}

	//}

	if (auto* const GameState = Cast<AKaijuKolosseumGameState>(GetWorld()->GetGameState()))
	{
		GameState->SetGameState(EGameState::Battle);
		GameState->UpdateCamera(EGameState::Battle, nullptr);
	}
	return EBTNodeResult::Succeeded;
}
