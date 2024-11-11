// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SwitchGameState.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGGAME_API UBTTask_SwitchGameState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UBTTask_SwitchGameState(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector GameStateSwitchedKey;
};
