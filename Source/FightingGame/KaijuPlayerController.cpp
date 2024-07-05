// Fill out your copyright notice in the Description page of Project Settings.


#include "KaijuPlayerController.h"
#include "Misc/Bitflags.h"
#include "InputMappingContext.h"
#include "FightingGameCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/InputSettings.h"


AKaijuPlayerController::AKaijuPlayerController()
{
	Inputs = 0;

}

void AKaijuPlayerController::SetupInputComponent()
{
	if (GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
			}
		}
	}

	if (InputComponent == NULL)
	{
		InputComponent = NewObject<UEnhancedInputComponent>(this, UInputSettings::GetDefaultInputComponentClass(), TEXT("PC_InputComponent0"));
		InputComponent->RegisterComponent();
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	//Jump Buttons
	if (IsValid(InputActions.PressUp))
		Input->BindAction(InputActions.PressUp.Get(), ETriggerEvent::Triggered, this, &AKaijuPlayerController::PressUp);
	if (IsValid(InputActions.PressUp))
		Input->BindAction(InputActions.ReleaseUp.Get(), ETriggerEvent::Triggered, this, &AKaijuPlayerController::ReleaseUp);
	//Forward Movement
	if (IsValid(InputActions.PressUp))
		Input->BindAction(InputActions.PressForward.Get(), ETriggerEvent::Triggered, this, &AKaijuPlayerController::PressForward);
	if (IsValid(InputActions.PressUp))
		Input->BindAction(InputActions.ReleaseForward.Get(), ETriggerEvent::Triggered, this, &AKaijuPlayerController::ReleaseForward);
}

void AKaijuPlayerController::PressUp()
{
	Inputs |= INP_8;
}

void AKaijuPlayerController::ReleaseUp()
{
	Inputs = Inputs &~ INP_8; //Used for performance, rather than looking at the enum again. Also will leave all other future states unaffected. 
}

void AKaijuPlayerController::PressForward()
{
	Inputs |= INP_6;
}

void AKaijuPlayerController::ReleaseForward()
{
	Inputs = Inputs & ~INP_6; //Used for performance, rather than looking at the enum again. Also will leave all other future states unaffected. 
}



