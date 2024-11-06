
#include "Gameplay/AI/Custom Tasks/Overworld/BTTask_FindRandLocation.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Gameplay/Controllers/KaijuAIController.h"

UBTTask_FindRandLocation::UBTTask_FindRandLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_FindRandLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get AI controller and its npc. 
	if (auto* const controller = Cast<AKaijuAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const npc = controller->GetPawn())
		{
			//Obtain npc location to use as an origin
			auto const Origin = npc->GetActorLocation();

			//Get the navigation system and generate a random location
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}

				//Finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;

			}
		}
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_FindRandLocation::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
