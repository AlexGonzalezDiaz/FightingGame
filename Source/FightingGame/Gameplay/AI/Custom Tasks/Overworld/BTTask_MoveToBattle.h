// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	bool bIsMoving;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector GameStateSwitchedKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector SpawnPartnerKey;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess ="true"))
	float InFrontOfPlayer;
	
};
