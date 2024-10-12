// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Controllers/TrainerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/InputSettings.h"


void ATrainerController::SetupInputComponent()
{
	// Get the local player
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	int32 ControllerId = LocalPlayer ? LocalPlayer->GetControllerId() : -1;

	UE_LOG(LogTemp, Log, TEXT("SetupInputComponent called for Trainer Controller ID: %d"), ControllerId);

	if (LocalPlayer)
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
				UE_LOG(LogTemp, Log, TEXT("Added Input Mapping Context for Controller ID: %d"), ControllerId);
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
	if (IsValid(InputActions.Move))
		Input->BindAction(InputActions.Move.Get(), ETriggerEvent::Triggered, this, &ATrainerController::Move);
}

void ATrainerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	int32 ControllerId = LocalPlayer ? LocalPlayer->GetControllerId() : -1;

	UE_LOG(LogTemp, Log, TEXT("Controller %d possessed a pawn"), ControllerId);

	// Set up input component here instead of in BeginPlay
	SetupInputComponent();
}

void ATrainerController::Move(const FInputActionValue& Value)
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

