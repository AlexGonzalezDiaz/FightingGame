// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TrainerController.generated.h"

//Forward Declarations
class UEnhancedInputComponent;
class UInputMappingContext;
class ATrainerCharacter;

/**
 * 
 */
USTRUCT()
struct FExploreInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> Move;

	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> Interact;
};

UCLASS()
class FIGHTINGGAME_API ATrainerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category = "Input")
	FExploreInputActions InputActions;
	UPROPERTY(EditAnywhere)
	bool InteractBtn = false;

protected:
	void Move(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
private:
	void SetupInputComponent();
	void OnPossess(APawn* InPawn) override;

};
