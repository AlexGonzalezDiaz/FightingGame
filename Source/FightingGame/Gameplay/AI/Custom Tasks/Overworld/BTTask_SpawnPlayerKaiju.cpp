// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/AI/Custom Tasks/Overworld/BTTask_SpawnPlayerKaiju.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Main/KaijuKolosseumGameState.h"

UBTTask_SpawnPlayerKaiju::UBTTask_SpawnPlayerKaiju(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Spawn Partner Kaiju";
}

EBTNodeResult::Type UBTTask_SpawnPlayerKaiju::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UE_LOG(LogTemp, Log, TEXT("Executing Task."));
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) return EBTNodeResult::Failed;

    // Check if the game state has been switched
    bool IsDoneMoving = BlackboardComp->GetValueAsBool(SpawnPartnerKey.SelectedKeyName);
    UE_LOG(LogTemp, Log, TEXT("Executing Task %s."), IsDoneMoving ? TEXT("true") : TEXT("false"));
    if (IsDoneMoving)
    {

        if (auto* const GameState = Cast<AKaijuKolosseumGameState>(GetWorld()->GetGameState()))
        {
            UE_LOG(LogTemp, Log, TEXT("Calling Spawn partner."));
            GameState->SpawnPartner(SpawnDistance);

            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}
