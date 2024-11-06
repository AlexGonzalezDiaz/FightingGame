
#include "Gameplay/Controllers/TrainerController.h"
#include "Gameplay/Controllers/KaijuAIController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/InputSettings.h"
#include "EngineUtils.h"


void ATrainerController::SetupInputComponent()
{
	// Get the local player
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	int32 ControllerId = LocalPlayer ? LocalPlayer->GetControllerId() : -1;

	if (LocalPlayer)
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
	if (IsValid(InputActions.Move))
		Input->BindAction(InputActions.Move.Get(), ETriggerEvent::Triggered, this, &ATrainerController::Move);
	if (IsValid(InputActions.Interact))
		Input->BindAction(InputActions.Interact.Get(), ETriggerEvent::Triggered, this, &ATrainerController::Interact);

}

void ATrainerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	int32 ControllerId = LocalPlayer ? LocalPlayer->GetControllerId() : -1;

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

void ATrainerController::Interact(const FInputActionValue& Value)
{
	// Notify all AI controllers
	for (TActorIterator<AKaijuAIController> It(GetWorld()); It; ++It)
	{
		AKaijuAIController* AIController = *It;
		AIController->OnPlayerPressedInteractButton();
	}
	
}

