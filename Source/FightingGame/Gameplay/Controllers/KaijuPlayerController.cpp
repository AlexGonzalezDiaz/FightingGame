// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Controllers/KaijuPlayerController.h"
#include "Misc/Bitflags.h"
#include "InputMappingContext.h"
#include "Gameplay/Actors/FightingGameCharacter.h"
#include "Gameplay/Controllers/KaijuAIController.h"
#include "Main/KaijuKolosseumGameState.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/InputSettings.h"
#include "EngineUtils.h"


AKaijuPlayerController::AKaijuPlayerController()
{
	Inputs = 0;
}

void AKaijuPlayerController::SetupInputComponent()
{
	// Get the local player
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	int32 ControllerId = LocalPlayer ? LocalPlayer->GetControllerId() : -1;
	GameState = GetWorld()->GetGameState<AKaijuKolosseumGameState>();

	UE_LOG(LogTemp, Log, TEXT("SetupInputComponent called for Kaiju Controller ID: %d"), ControllerId); 
	if (GameState)
	{
		if (LocalPlayer && GameState->CurrentGameState == EGameState::Battle)
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				SwitchInputMapping(InputMapping.LoadSynchronous());
				UE_LOG(LogTemp, Log, TEXT("Assigning Battle input mapping"));
			}
		}
		else if (LocalPlayer && GameState->CurrentGameState == EGameState::Overworld)
		{
			SwitchInputMapping(ExploringMapping.LoadSynchronous());
			UE_LOG(LogTemp, Log, TEXT("Assigning Overworld input mapping"));
		}
	}

	if (InputComponent == NULL)
	{
		InputComponent = NewObject<UEnhancedInputComponent>(this, UInputSettings::GetDefaultInputComponentClass(), TEXT("PC_InputComponent0"));
		InputComponent->RegisterComponent();
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	//Jump Buttons
	if (GameState->CurrentGameState == EGameState::Battle)
	{
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
	else if (GameState->CurrentGameState == EGameState::Overworld)
	{
		UE_LOG(LogTemp, Log, TEXT("Inside the overworld input calls."));
		if (IsValid(RPGActions.Move))
			Input->BindAction(RPGActions.Move.Get(), ETriggerEvent::Triggered, this, &AKaijuPlayerController::Move);
		if (IsValid(RPGActions.Interact))
			Input->BindAction(RPGActions.Interact.Get(), ETriggerEvent::Triggered, this, &AKaijuPlayerController::Interact);
	}
		

	
}

void AKaijuPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	int32 ControllerId = LocalPlayer ? LocalPlayer->GetControllerId() : -1;

	UE_LOG(LogTemp, Log, TEXT("Controller %d possessed a pawn"), ControllerId);
	UE_LOG(LogTemp, Log, TEXT("Controller %d possessed a pawn"), GetOwner());

	// Set up input component here instead of in BeginPlay
	SetupInputComponent();

}

void AKaijuPlayerController::PressUp()
{
	Inputs |= INP_8;

	UE_LOG(LogTemp, Log, TEXT("Press Up."));
}

void AKaijuPlayerController::ReleaseUp()
{
	Inputs = Inputs &~ INP_8; //Used for performance, rather than looking at the enum again. Also will leave all other future states unaffected. 
	
}

void AKaijuPlayerController::PressForward()
{
	Inputs |= INP_6;
	UE_LOG(LogTemp, Log, TEXT("Press Forward."));
}

void AKaijuPlayerController::ReleaseForward()
{
	Inputs = Inputs & ~INP_6; //Used for performance, rather than looking at the enum again. Also will leave all other future states unaffected. 
}

void AKaijuPlayerController::SwitchInputMapping(UInputMappingContext* NewMapping)
{
	UEnhancedInputLocalPlayerSubsystem* InputSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
	// Remove the old mapping(
	if (!InputMapping.IsNull() || !ExploringMapping.IsNull())
	{
		if(InputSystem)
			InputSystem->RemoveMappingContext(InputMapping.LoadSynchronous());
	}

	// Add the new mapping
	if (NewMapping)
	{
		if (InputSystem)
		{
			InputSystem->AddMappingContext(NewMapping, 0);
			UE_LOG(LogTemp, Log, TEXT("Switched Input Mapping for Controller ID: %d"), GetLocalPlayer()->GetControllerId());
		}
			
	}

}

void AKaijuPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (GetPawn())
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
		GetPawn()->AddMovementInput(RightDirection, MovementVector.X);

	}
}

void AKaijuPlayerController::Interact(const FInputActionValue& Value)
{
	// Notify all AI controllers
	for (TActorIterator<AKaijuAIController> It(GetWorld()); It; ++It)
	{
		AKaijuAIController* AIController = *It;
		AIController->OnPlayerPressedInteractButton();
	}

}



