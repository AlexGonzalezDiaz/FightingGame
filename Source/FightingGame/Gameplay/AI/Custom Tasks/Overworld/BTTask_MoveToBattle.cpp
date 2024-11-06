// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/Custom Tasks/Overworld/BTTask_MoveToBattle.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Gameplay/Controllers/KaijuAIController.h"

UBTTask_MoveToBattle::UBTTask_MoveToBattle(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Move Wild Kaiju in Front of Player";
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveToBattle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Controller = Cast<AKaijuAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const npc = Controller->GetPawn())

			auto const Origin = npc->GetActorLocation();

			AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

			FVector TrainerForwardVector = Player->GetActorForwardVector() * 800.f;
			FVector TrainerLocation = Player->GetActorLocation();
			FVector NewLocation = TrainerLocation + (TrainerForwardVector* 800.f);

			EPathFollowingRequestResult::Type MoveResult = Controller->MoveTo(NewLocation);

			//Finish with success
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
	}
		
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_MoveToBattle::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}
