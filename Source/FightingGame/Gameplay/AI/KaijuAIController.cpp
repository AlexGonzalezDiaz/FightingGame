
#include "Gameplay/Actors/AICharacter.h"
#include "Gameplay/AI/KaijuAIController.h"
#include "BehaviorTree/BehaviorTree.h"

AKaijuAIController::AKaijuAIController(FObjectInitializer const& ObjectInitializer)
{

}

void AKaijuAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AAICharacter* const npc = Cast<AAICharacter>(InPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* BB;
			UseBlackboard(tree->BlackboardAsset, BB);
			Blackboard = BB;
			RunBehaviorTree(tree);
		}
	}
}
