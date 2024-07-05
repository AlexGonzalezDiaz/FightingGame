// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "main/StateMachineFG.h"
#include "Main/StateData.h"
#include "InputActionValue.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h "
#include "FightingGameCharacter.generated.h"

class AKaijuKolosseumGameState;

UCLASS(config=Game)
class AFightingGameCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	AFightingGameCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FGCollisions, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* fightingGameBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FGCollisions, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* proximityGameBox;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;
	
public:

	//---++       STATEHANDLING     ++---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StateMachine")
	int32 Inputs;

	UPROPERTY(VisibleAnywhere, Category = "State Machine")
	bool bStateComplete = false;

	UPROPERTY(EditAnywhere)
	AKaijuKolosseumGameState* GameState;

	UPROPERTY()
	FStateMachineFG SavedStateMachine; //RecentChange. 

	UPROPERTY(EditDefaultsOnly, Category = "Data Asset")
	UStateData* DataAsset;

	//---++ STATEHANDLING ++---


	//---++       MOVEMENT     ++---
	UPROPERTY()
	FVector YVec; //Currently initialized in the constructor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 PosX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 PosY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 PosZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 SpeedX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 SpeedY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 SpeedZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 RateSpeedX = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 RateSpeedY = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 RateSpeedZ = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 Gravity = 1900;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 GroundLevel;

	//Set Height inside state machine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 JumpHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	EStateFlags CharacterState;

	//---++       MOVEMENT     ++---
	//Set Height inside state machine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom JumpMovement")
	int32 FwlkSpeed;



	UPROPERTY(BlueprintReadOnly)
	int32 PlayerIndex; //Keep track of which is player 1 and player 2

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAnimSequenceBase> AnimSequence;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAnimSequenceBase> BlendAnimSequence;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float baseHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock-On")
	bool isLockedOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFightingGameCharacter* otherPlayer;

	UState* PlayerStates;

	UPROPERTY(EditAnywhere, Category = "Data")
	UStateData* PlayerStatesData;

	FVector jumpVelocity;
	float previousZJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float flipInput;

	//The amount of time the character will be stunned (hitstun, blockstun, or from a stunning attack)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float stunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float hitStopTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool canMove;


	//The timer handle for all stuns (hitsuns, blockstuns, and stunning attacks)
	FTimerHandle stunTimerHandle;
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	AActor* hurtbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USceneComponent* characterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TArray<USceneComponent*> capsuleChildren;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	bool isFlipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	FTransform transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	FVector scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	float dmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasLightAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasJumpLightAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasJumpMediumAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasJumpeHeavyAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasMeduimAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasHeavyAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasSpecialAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool hasLandedHit;

	UFUNCTION(BlueprintCallable)
	void dmgAmntCalc(float dmgAmount, float _stunTime, float _hitStopTime, float _pushbackAmount, float _launchAmount, FVector _hitLocation);

	void SetPreviousVelocity();

	UFUNCTION(BlueprintCallable)
	void CustomLaunchCharacter(FVector _LaunchVelocity, bool _shouldOverrideXY, bool _shouldOverrideZ, bool _shouldIgnoreCharacterCollision = false);

	void IgnorePlayerToPlayerCollision();

	UFUNCTION(BlueprintCallable)
	void performPushback(float _pushbackAmount, float _launchAmount, bool _hasBlocked);

	UFUNCTION(BlueprintImplementableEvent)
	void colliderSlide(FVector _start, FVector _end);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDamageEffects(FVector _hitLocation);

	void Update();

	/** Called for movement input */
	void Move();

	void UpdateVisuals();
	/** Updating the state machine using frames instead of tick*/


protected:
	//Simple Box Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collsion Boxes")
	TArray<UStaticMeshComponent*> simpleBoxCollisions;

	//ForwardVector for movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector Velocity;



	// Check for Attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasNormalAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool isSideStep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isJumping;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	float jumpDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	int maxJumpCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	int jumpCount;

	UFUNCTION(BlueprintCallable)
	bool IsOnGround();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void LightAttack();

	void SpecialAttack();

	void Tick(float DeltaTime);

	//Enter the Stun state
	void BeginStun();

	//Add hitsop
	void BeginHitstop(float _hitStopTime);

	//End the Stun state
	void EndStun();

	void EndHitstop();

	// Lock on oppponent active character
	void LockOn();
			
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	//Override the ACharacter and APawn functionality to have more control over jumps and landings.
	virtual void Landed(const FHitResult& Hit) override;

	/*virtual void Jump() override;*/
	virtual void StopJumping() override;
};

