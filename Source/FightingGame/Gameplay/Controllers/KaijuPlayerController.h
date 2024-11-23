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
class AKaijuKolosseumGameState;

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

USTRUCT()
struct FRPGInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> Move;
	UPROPERTY(EditAnywhere)
	TObjectPtr<const UInputAction> Interact;
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
	TSoftObjectPtr<UInputMappingContext> ExploringMapping;
	UPROPERTY(EditAnywhere, Category = "Input")
	FBattleInputActions InputActions;
	UPROPERTY(EditAnywhere, Category = "Input")
	FRPGInputActions RPGActions;

	int Inputs;

protected:
	void PressUp();
	void ReleaseUp();
	void PressForward();
	void ReleaseForward();

	void SwitchInputMapping(UInputMappingContext* NewMapping);

	/*
	* RPG Controlls and functions
	*/
	void Move(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	UPROPERTY()
	TObjectPtr<AFightingGameCharacter> PlayerCharacter = nullptr;

	UPROPERTY()
	AKaijuKolosseumGameState* GameState;


	virtual void SetupInputComponent() override;

	void OnPossess(APawn* InPawn) override;

};
