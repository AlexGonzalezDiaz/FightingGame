// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToBattle.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGGAME_API UBTTask_MoveToBattle : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_MoveToBattle(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess ="true"))
	float InFrontOfPlayer;
	
};
