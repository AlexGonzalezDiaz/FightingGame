#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_SenseTrainer.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGGAME_API UBTDecorator_SenseTrainer : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	

public: 
	UBTDecorator_SenseTrainer();



protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector PlayerKeySelector;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector InteractButtonKeySelector;


};
