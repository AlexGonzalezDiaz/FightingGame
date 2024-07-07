// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h "
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "FightingGameGameMode.h"
#include "Misc/Globals.h"
#include "KaijuKolosseumGameState.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputComponent.h"
#include "KaijuMovementComponent.h"
#include "EnhancedInputSubsystems.h"

//////////////////////////////////////////////////////////////////////////
// AFightingGameCharacter

AFightingGameCharacter::AFightingGameCharacter()
{
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
	fightingGameBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBox"));
	fightingGameBox->SetupAttachment(GetMesh());
	proximityGameBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProximityBox"));
	proximityGameBox->SetupAttachment(GetMesh());
	
	YVec = GetActorForwardVector();

	

	 /*Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	 are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)*/
	
	//*******CURRENTLY DEVELOPING*********//
	
	JumpHeight = 35000;
	FwlkSpeed = 2000;
	SpeedX = 0;
	SpeedY = 0;
	SpeedZ = 0;
	Gravity = 1900;
	//*******CURRENTLY DEVELOPING**********//

	otherPlayer = nullptr;
	characterMesh = nullptr;
	hurtbox = nullptr;
	capsuleChildren.SetNum(0);
	/*characterState = ECharacterState::VE_Default;*/
	transform = FTransform();
	scale = FVector(0.0f, 0.0f, 0.0f);
	jumpVelocity = FVector(0.0f, 0.0f, 0.0f);
	previousZJump = 0.0f;
	baseHealth = 1.00f;
	wasNormalAttackUsed = false;
	dmg = 0.0f;
	isLockedOn = false;
	isFlipped = false;

	flipInput = 1.0f;
	canMove = true;
	stunTime = 0.0f;
	hitStopTime = 0.0f;
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


	isJumping = false; 
	jumpDistance = 400.0f;
	maxJumpCount = 2;
	jumpCount = 0;

}
void AFightingGameCharacter::Update()
{
	SavedStateMachine.Update(Inputs);
	Move();
	CharacterState = SavedStateMachine.CurrState;
}


void AFightingGameCharacter::Move()
{
	// Set SpeedY in blueprints to the JumpHeight. 
	SpeedY = SpeedY * RateSpeedZ / 100;
	SpeedZ = SpeedZ * RateSpeedZ / 100;

	//UE_LOG(LogTemp, Warning, TEXT("First PosZ : %i"), PosZ);
	// Jump updated when speed is first set and keep updating while in the air.
	if (SpeedZ > 0 || PosZ > GroundLevel)
	{
		PosZ += SpeedZ;		
		//UE_LOG(LogTemp, Warning, TEXT("SpeedZ is : %i"), SpeedZ);
		//UE_LOG(LogTemp, Warning, TEXT("PosZ added by SpeedZ : %i"), PosZ);
		if (PosZ > GroundLevel)
			SpeedZ -= Gravity; //Subtract gravity as long as we are above the ground.
		else
		{
			SpeedZ = 0;
			PosZ = GroundLevel;
		}
	}

	if (SpeedY > 0)
	{
		PosY += SpeedY;
	}

	UpdateVisuals();
}

void AFightingGameCharacter::UpdateVisuals()
{
	if (SavedStateMachine.StateStarted)
	{
		FVector OffsetLocation = FVector(static_cast<float>(PosX) / COORD_SCALE, static_cast<float>(PosY) / COORD_SCALE, static_cast<float>(PosZ) / COORD_SCALE);
		FVector NewLocation = GameState->BattleData.StartLocations[PlayerIndex] + OffsetLocation;
		SetActorLocation(NewLocation);
	}
}

void AFightingGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	PosX = GetActorLocation().X;
	PosY = GetActorLocation().Y;
	PosZ = GetActorLocation().Z;

	SavedStateMachine.Parent = this;
	SavedStateMachine.LoadStates(this, DataAsset);
	LockOn();
}

void AFightingGameCharacter::Landed(const FHitResult& Hit)
{
	/*if (characterState == ECharacterState::VE_Jumping) {

		characterState = ECharacterState::VE_Default;
	}

	if (characterState == ECharacterState::VE_Launched)
	{

	    GetCharacterMovement()->GravityScale = gravityScale;
		characterState = ECharacterState::VE_Default;
	}*/

	//This block is used to re-adjust the characters position when landing on the head of the player
	if (otherPlayer && Hit.GetActor() == otherPlayer)
	{
		/*FVector vectorRandom = fightingGameBox->Bounds.BoxExtent;*/
		/*UE_LOG(LogTemp, Warning, TEXT("Landed"));
		fightingGameBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		otherPlayer->fightingGameBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);*/
		
		//Set Timer doesn't work if the function you are calling has a parameter inside.
		/*GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFightingGameCharacter::IgnorePlayerToPlayerCollision, 0.01f, false);*/

		//fightingGameBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//otherPlayer->fightingGameBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		float offset = 60.0;
		FVector forwardVector = otherPlayer->GetActorForwardVector().GetAbs();
		FVector otherPlayerLocation = otherPlayer->GetActorLocation();
		
		FVector_NetQuantizeNormal hitLocation = Hit.ImpactPoint;
		
		
		if (hitLocation.Y > otherPlayerLocation.Y )
		{
			offset *= 1.0;
			FVector newLocation = (forwardVector * offset) + otherPlayer->GetActorLocation();
			colliderSlide(GetActorLocation(), FVector(newLocation.X, newLocation.Y, otherPlayerLocation.Z));
		}
		else
		{
			offset *= -1.0;
			FVector newLocation = (forwardVector * offset) + otherPlayer->GetActorLocation();
			colliderSlide(GetActorLocation(), FVector(newLocation.X, newLocation.Y, otherPlayerLocation.Z));
		}
		
	}

	jumpCount = 0;

}


void AFightingGameCharacter::dmgAmntCalc(float dmgAmount, float _stunTime, float _hitStopTime, float _pushbackAmount, float _launchAmount, FVector _hitLocation)
{
	//baseHealth -= dmgAmount;

	//characterState = ECharacterState::VE_Stunned;
	//stunTime = _stunTime;

	//if (stunTime > 0.0f)
	//{
	//	characterState = ECharacterState::VE_Stunned;
	//	BeginStun();
	//}
	//

	//if (otherPlayer) {
	//	otherPlayer->hasLandedHit = true;
	//	PlayDamageEffects(_hitLocation);
	//	if (otherPlayer->characterState == ECharacterState::VE_Jumping) {
	//		otherPlayer->BeginHitstop(_hitStopTime);
	//	}
	//	
	//	//otherPlayer->performPushback(_pushbackAmount, 0.0f, false);
	//}

	//performPushback(_pushbackAmount, _launchAmount, false);

	//if (baseHealth < 0.00f)
	//{
	//	baseHealth = 0.00f;
	//}
}

void AFightingGameCharacter::SetPreviousVelocity()
{
	//jumpVelocity = GetVelocity();
	//UE_LOG(LogTemp, Warning, TEXT("Stored Velocity p1 %s and get velocity is: %s"), *jumpVelocity.ToString(), *GetVelocity().ToString());
}

void AFightingGameCharacter::CustomLaunchCharacter(FVector _LaunchVelocity, bool _shouldOverrideXY, bool _shouldOverrideZ, bool _shouldIgnoreCharacterCollision)
{

	LaunchCharacter(_LaunchVelocity, _shouldOverrideXY, _shouldOverrideZ);
}

void AFightingGameCharacter::IgnorePlayerToPlayerCollision()
{
	fightingGameBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	otherPlayer->fightingGameBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AFightingGameCharacter::performPushback(float _pushbackAmount, float _launchAmount, bool _hasBlocked)
{
	//FVector launchDirection = otherPlayer->GetActorForwardVector();
	//float launchDirection_X = launchDirection.X * _pushbackAmount; //Consider making a global variable for this, like a general direction & x & y
	//float launchDirection_Y = launchDirection.Y * _pushbackAmount;

	//if (_launchAmount > 0.0f || _launchAmount < 0.0f)
	//{
	//	GetCharacterMovement()->GravityScale = 0.6;
	//	characterState = ECharacterState::VE_Launched;
	//	CustomLaunchCharacter(FVector(launchDirection_X, launchDirection_Y, _launchAmount), false, false);

	//	UE_LOG(LogTemp, Warning, TEXT("Gravity scale launched is %f"), GetCharacterMovement()->GravityScale);
	//	_launchAmount = 0.0f;

	//}

	//else
	//{
	//	CustomLaunchCharacter(FVector(launchDirection_X, launchDirection_Y, 0.0f), false, false);
	//}
	
}
void AFightingGameCharacter::Tick(float DeltaTime)
{
}






void AFightingGameCharacter::LightAttack()
{
}

void AFightingGameCharacter::SpecialAttack()
{
}

void AFightingGameCharacter::BeginStun()
{
	
	canMove = false;
	//fightingGameBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorld()->GetTimerManager().SetTimer(stunTimerHandle, this, &AFightingGameCharacter::EndStun, stunTime, false);
}

void AFightingGameCharacter::BeginHitstop(float _hitStopTime)
{
	//previousZJump = GetVelocity().Z;

	//if (characterState != ECharacterState::VE_Stunned || characterState != ECharacterState::VE_Launched) {
	//	GetCharacterMovement()->GravityScale = 0.0f;
	//	GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
	//	otherPlayer->GetCharacterMovement()->GravityScale = 0.0f;
	//	otherPlayer->GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
	//}
	//else {
	//	EndHitstop();
	//}
	////Timer that will call the EndHitstop Function
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFightingGameCharacter::EndHitstop, _hitStopTime, false);
}

void AFightingGameCharacter::EndStun()
{
	//canMove = true;
	////IgnorePlayerToPlayerCollision();
	//if(characterState != ECharacterState::VE_Launched)
	//{
	//	
	//	characterState = ECharacterState::VE_Default;
	//}
}

void AFightingGameCharacter::EndHitstop()
{
	
	//if (characterState != ECharacterState::VE_Stunned || characterState != ECharacterState::VE_Launched) {
	//	GetCharacterMovement()->GravityScale = gravityScale;
	//	GetCharacterMovement()->Velocity = FVector(jumpVelocity.X, jumpVelocity.Y, previousZJump);
	//	otherPlayer->GetCharacterMovement()->GravityScale = gravityScale;
	//	//otherPlayer->GetCharacterMovement()->Velocity = FVector(0.0f, 0.0f, 0.0f);
	//	UE_LOG(LogTemp, Warning, TEXT("End Hitstop"));

	//}
}

void AFightingGameCharacter::LockOn()
{
}
	


//////////////////////////////////////////////////////////////////////////
// Input

void AFightingGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//if (auto gameMode = Cast<AFightingGameGameMode>(GetWorld()->GetAuthGameMode()))
	//{
	//	if (gameMode->player1 == this)
	//	{

	//		// Set up action bindings
	//		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

	//			//Jumping
	//			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	//			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	//			//Moving
	//			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFightingGameCharacter::Move);

	//			//Looking
	//			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFightingGameCharacter::Look);

	//			//Attacking

	//			//PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AFightingGameCharacter::Attack);
	//		}
	//	}
	//}
}

bool AFightingGameCharacter::IsOnGround()
{
	// Implement proper ground detection here
	// This is a simplified example
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 10); // Check 10 units below the character

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
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




