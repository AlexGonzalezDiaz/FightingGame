// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FightingGameCharacter.generated.h"

UENUM(BlueprintType)
enum class EDirectionalInput : uint8
{
	VE_Default			UMETA(DisplayName = "NEUTRAL"),
	VE_ForwardInput		UMETA(DisplayName = "FWD_INPUT"),
	VE_BackwardInput	UMETA(DisplayName = "BCK_INPUT")
};

UCLASS(config=Game)
class AFightingGameCharacter : public ACharacter
{
	GENERATED_BODY()

	///** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	///** Follow camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* FollowCamera;
	
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
	AFightingGameCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float baseHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock-On")
	bool isLockedOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFightingGameCharacter* otherPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EDirectionalInput directionalInput;

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

	UFUNCTION(BlueprintCallable)
	void dmgAmntCalc(float dmgAmount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	float dmg;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasLightAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasMeduimAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasHeavyAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasSpecialAttackedUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	float flipInput;

protected:

	// Check for Attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool wasNormalAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool isSideStep;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void LightAttack();

	void SpecialAttack();

	void Tick(float DeltaTime);
			
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

};

