// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KaijuAIController.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGGAME_API AKaijuAIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit AKaijuAIController(FObjectInitializer const& ObjectInitializer);

protected:
	void OnPossess(APawn* InPawn) override;
};
