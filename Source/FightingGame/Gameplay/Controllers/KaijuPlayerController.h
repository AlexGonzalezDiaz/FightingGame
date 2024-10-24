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
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> PressForward;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> ReleaseForward;
};

UCLASS()
class FIGHTINGGAME_API AKaijuPlayerController : public APlayerController
{	

	GENERATED_BODY()

public:
	AKaijuPlayerController();

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category = "Input")
	FBattleInputActions InputActions;

	int Inputs;

protected:
	void PressUp();
	void ReleaseUp();
	void PressForward();
	void ReleaseForward();

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	UPROPERTY()
	TObjectPtr<AFightingGameCharacter> PlayerCharacter = nullptr;

	virtual void SetupInputComponent() override;

	void OnPossess(APawn* InPawn) override;

};
