// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Bitflags.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "KaijuPlayerController.generated.h"

// Forward Declarations
class UEnhancedInputComponent;
class UInputMappingContext;
class AFightingGameCharacter;

USTRUCT()
struct FBattleInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressUp;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseUp;
};

UCLASS(Abstract)
class FIGHTINGGAME_API AKaijuPlayerController : public APlayerController
{	
public:
	AKaijuPlayerController();

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category = "Input")
	FBattleInputActions InputActions;

	int Inputs;

protected:

	virtual void SetupInputComponent() override;

	/** Called for movement input */
	void HandleMove(const FInputActionValue& Value);

	void PressUp();
	void ReleaseUp();

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	UPROPERTY()
	TObjectPtr<AFightingGameCharacter> PlayerCharacter = nullptr;

	GENERATED_BODY()
};
