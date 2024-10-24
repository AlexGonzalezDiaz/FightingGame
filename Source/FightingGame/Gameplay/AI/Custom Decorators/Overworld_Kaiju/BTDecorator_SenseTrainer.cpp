
#include "BehaviorTree/BlackboardComponent.h"
#include "Gameplay/Actors/AICharacter.h  "
#include "AIController.h"
#include "Components/SphereComponent.h"
#include "Gameplay/AI/Custom Decorators/Overworld_Kaiju/BTDecorator_SenseTrainer.h"

class ATrainerCharacter;

UBTDecorator_SenseTrainer::UBTDecorator_SenseTrainer()
{
    NodeName = "Abort Patrol";
    bNotifyTick = true;
    bAllowAbortNone = false;
    bAllowAbortLowerPri = true;
    bAllowAbortChildNodes = true;
    FlowAbortMode = EBTFlowAbortMode::LowerPriority;
}

bool UBTDecorator_SenseTrainer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) return false;
    
    //Lesson learned, make sure to not write out the key, instead just use the function.selected key Name
    bool bIsPlayerInRange = BlackboardComp->GetValueAsBool(PlayerKeySelector.SelectedKeyName);
    bool bInteractButtonPressed = BlackboardComp->GetValueAsBool(InteractButtonKeySelector.SelectedKeyName);

   
    return bIsPlayerInRange && bInteractButtonPressed;
}

void UBTDecorator_SenseTrainer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    
    bool bConditionMet = CalculateRawConditionValue(OwnerComp, NodeMemory);


    if (bConditionMet)
    {
        UE_LOG(LogTemp, Warning, TEXT("Conditions met, requesting execution"));
        OwnerComp.RequestExecution(this);
    }
}
