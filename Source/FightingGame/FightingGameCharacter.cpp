// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "FightingGameGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "KaijuMovementComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AFightingGameCharacter

AFightingGameCharacter::AFightingGameCharacter(const FObjectInitializer& ObjectInitializer):
Super(ObjectInitializer.SetDefaultSubobjectClass<UKaijuMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	KaijuMovementComponent = Cast<UKaijuMovementComponent>(GetCharacterMovement());

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	//// Create a follow camera
	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	otherPlayer = nullptr;
	characterMesh = nullptr;
	hurtbox = nullptr;
	capsuleChildren.SetNum(0);
	characterState = ECharacterState::VE_Default;
	transform = FTransform();
	scale = FVector(0.0f, 0.0f, 0.0f);
	baseHealth = 1.00f;
	wasNormalAttackUsed = false;
	dmg = 0.0f;
	isLockedOn = false;
	isFlipped = false;

	flipInput = 1.0f;
	canMove = true;
	gravityScale = GetCharacterMovement()->GravityScale;
	stunTime = 0.0f;
	isSideStep = false;

	//Ground Normals and specials
	wasLightAttackedUsed = false;
	wasMeduimAttackedUsed = false;
	wasHeavyAttackedUsed = false;
	wasSpecialAttackedUsed = false;
	hasLandedHit = false;

	//Jump Normals
	wasJumpLightAttackedUsed = false;
	wasJumpMediumAttackUsed = false;
	wasJumpeHeavyAttackUsed = false;

}

void AFightingGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();


	if (auto gameMode = Cast<AFightingGameGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (gameMode->player1 == this)
		{
			//Add Input Mapping Context
			if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
			{
				if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
				{
					Subsystem->AddMappingContext(DefaultMappingContext, 0);
				}
			}
		}
	}
}

void AFightingGameCharacter::Landed(const FHitResult& Hit)
{
	if (characterState == ECharacterState::VE_Launched)
	{

	    //GetCharacterMovement()->GravityScale = gravityScale;
		characterState = ECharacterState::VE_Default;
		UE_LOG(LogTemp, Warning, TEXT("% f"), GetCharacterMovement()->GravityScale);
	}
	if (otherPlayer && Hit.GetActor() == otherPlayer)
	{
		float offset = 60.0;
		FVector forwardVector = otherPlayer->GetActorForwardVector().GetAbs();
		FVector otherPlayerLocation = otherPlayer->GetActorLocation();
		
		FVector_NetQuantizeNormal hitLocation = Hit.ImpactPoint;
		
		
		if (hitLocation.Y > otherPlayerLocation.Y )
		{
			offset *= 1.0;
			UE_LOG(LogTemp, Warning, TEXT("Player 1 %s"), *hitLocation.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Player 2  player 1 Y is further ahead %s"), *otherPlayer->GetActorLocation().ToString());
			UE_LOG(LogTemp, Warning, TEXT("Player 2  forward vector: %s "), *forwardVector.ToString());
			FVector maths = forwardVector * offset;
			FVector newLocation = (forwardVector * offset) + otherPlayer->GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("Player 2  maffs: %s "), *maths.ToString());
			colliderSlide(GetActorLocation(), FVector(newLocation.X, newLocation.Y, otherPlayerLocation.Z));
		}
		else
		{
			offset *= -1.0;
			UE_LOG(LogTemp, Warning, TEXT("Player 1 %s"), *hitLocation.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Player 2  player 1 Y is behind %s"), *otherPlayer->GetActorLocation().ToString());
			UE_LOG(LogTemp, Warning, TEXT("Player 2  forward vector: %s "), *forwardVector.ToString());
			FVector maths = forwardVector * offset;
			FVector newLocation = (forwardVector * offset) + otherPlayer->GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("Player 2  maffs: %s "), *maths.ToString());
			colliderSlide(GetActorLocation(), FVector(newLocation.X, newLocation.Y, otherPlayerLocation.Z));
		}
		
	}
}

void AFightingGameCharacter::dmgAmntCalc(float dmgAmount, float _stunTime, float _pushbackAmount, float _launchAmount)
{
	baseHealth -= dmgAmount;

	characterState = ECharacterState::VE_Stunned;
	stunTime = _stunTime;

	if (stunTime > 0.0f)
	{
		characterState = ECharacterState::VE_Stunned;
		BeginStun();
	}
	

	if (otherPlayer) {
		otherPlayer->hasLandedHit = true;
		otherPlayer->performPushback(_pushbackAmount, 0.0f, false);
	}

	performPushback(_pushbackAmount, _launchAmount, false);

	if (baseHealth < 0.00f)
	{
		baseHealth = 0.00f;
	}
}

void AFightingGameCharacter::performPushback(float _pushbackAmount, float _launchAmount, bool _hasBlocked)
{
	FVector launchDirection = otherPlayer->GetActorForwardVector();
	float launchDirection_X = launchDirection.X * _pushbackAmount; //Consider making a global variable for this, like a general direction & x & y
	float launchDirection_Y = launchDirection.Y * _pushbackAmount;

	if (_launchAmount > 0.0f)
	{
		//GetCharacterMovement()->GravityScale = gravityScale;
		characterState = ECharacterState::VE_Launched;
		LaunchCharacter(FVector(launchDirection_X, launchDirection_Y, _launchAmount), false, false);

		UE_LOG(LogTemp, Warning, TEXT("Gravity scale before is % f"), GetCharacterMovement()->GravityScale);
		_launchAmount = 0.0f;

	}
	else
	{
		LaunchCharacter(FVector(launchDirection_X, launchDirection_Y, 0.0f), false, false);
	}
	
}


void AFightingGameCharacter::LightAttack()
{
}

void AFightingGameCharacter::SpecialAttack()
{
}

void AFightingGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
}

void AFightingGameCharacter::BeginStun()
{
	UE_LOG(LogTemp, Warning, TEXT("Stun"));
	canMove = false;
	GetWorld()->GetTimerManager().SetTimer(stunTimerHandle, this, &AFightingGameCharacter::EndStun, stunTime, false);
}

void AFightingGameCharacter::EndStun()
{
	if(characterState != ECharacterState::VE_Launched)
	{
		characterState = ECharacterState::VE_Default;
	}
	canMove = true;
}
	


//////////////////////////////////////////////////////////////////////////
// Input

void AFightingGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (auto gameMode = Cast<AFightingGameGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (gameMode->player1 == this)
		{

			// Set up action bindings
			if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

				//Jumping
				EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
				EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

				//Moving
				EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFightingGameCharacter::Move);

				//Looking
				EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFightingGameCharacter::Look);

				//Attacking

				//PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AFightingGameCharacter::Attack);
			}
		}
	}
}

void AFightingGameCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	const FVector2D directionVector = Value.Get<FVector2d>();


	if (Controller != nullptr)
	{
		if (canMove && characterState != ECharacterState::VE_Launched) {
			if (isFlipped) {
				MovementVector = MovementVector * -1.0f;
			}
			// Attempting to get the right button key press and setting our enum value. 
			if (MovementVector.Y > 0.02f)
			{
				characterState = ECharacterState::VE_ForwardInput;
			}
			else if (MovementVector.Y < 0.02f)
			{
				characterState = ECharacterState::VE_BackwardInput;
			}
			else
			{
				characterState = ECharacterState::VE_Default;
			}

			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement 
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}

	}
}

void AFightingGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




