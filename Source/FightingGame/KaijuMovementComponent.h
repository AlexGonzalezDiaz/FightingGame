// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KaijuMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTINGGAME_API UKaijuMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
protected:
	virtual void JumpOff(AActor* MovementBaseActor) override;
	virtual FVector GetSlideDirection(AActor* BaseActor) const;

public:
	UKaijuMovementComponent();
};