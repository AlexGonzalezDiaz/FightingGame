// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/Custom Tasks/Overworld/BTTask_MoveToBattle.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Gameplay/Controllers/KaijuAIController.h"

UBTTask_MoveToBattle::UBTTask_MoveToBattle(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Move Wild Kaiju in Front of Player";
	bNotifyTaskFinished = true;
    bNotifyTick = true;
	InFrontOfPlayer = 700;
}

EBTNodeResult::Type UBTTask_MoveToBattle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) return EBTNodeResult::Failed;

    // Check if the game state has been switched
    bool IsGameStateSwitched = BlackboardComp->GetValueAsBool(GameStateSwitchedKey.SelectedKeyName);
    if (!IsGameStateSwitched)
    {
        // If game state hasn't been switched, fail the task
        return EBTNodeResult::Failed;
    }

    if (auto* const Controller = Cast<AKaijuAIController>(OwnerComp.GetAIOwner()))
    {
        if (auto* const npc = Controller->GetPawn())
        {
            AActor* Player = Cast<AActor>(BlackboardComp->GetValueAsObject(GetSelectedBlackboardKey()));
            if (!Player)
            {
                {
                    // If game state hasn't been switched, fail the task
                    return EBTNodeResult::Failed;
                }
            }
            FVector TrainerForwardVector = Player->GetActorForwardVector();
            FVector TrainerLocation = Player->GetActorLocation();
            FVector NewLocation = TrainerLocation + (TrainerForwardVector * InFrontOfPlayer);

            EPathFollowingRequestResult::Type MoveResult = Controller->MoveTo(NewLocation);

            if (MoveResult == EPathFollowingRequestResult::RequestSuccessful)
            {
                // Start checking for movement completion
                bIsMoving = true;
                return EBTNodeResult::InProgress;
                //BlackboardComp->SetValueAsBool(SpawnPartnerKey.SelectedKeyName, true);
                //UE_LOG(LogTemp, Log, TEXT("Inside of if statement SpawnKey is %s."), IsSpawnReady ? TEXT("true") : TEXT("false"));
            }
            else
            {
                return EBTNodeResult::Succeeded;
            }
        }
    }

    return EBTNodeResult::Failed;
}

void UBTTask_MoveToBattle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    BlackboardComp = OwnerComp.GetBlackboardComponent();
 
    if (auto* const Controller = Cast<AKaijuAIController>(OwnerComp.GetAIOwner()))
    {
        if (Controller->GetMoveStatus() == EPathFollowingStatus::Idle)
        {
            bool IsSpawnReady = BlackboardComp->GetValueAsBool(GameStateSwitchedKey.SelectedKeyName);
            // Movement completed
            BlackboardComp->SetValueAsBool(SpawnPartnerKey.SelectedKeyName, true);
            UE_LOG(LogTemp, Log, TEXT("Inside of if statement SpawnKey is %s."), IsSpawnReady ? TEXT("true") : TEXT("false"));
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        }
    }
   
}
