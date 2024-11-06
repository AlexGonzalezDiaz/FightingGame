// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Main/KaijuKolosseumGameState.h"
#include "TrainerCharacter.generated.h"

class AAICharacter;

UCLASS()
class FIGHTINGGAME_API ATrainerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATrainerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* TamerCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RPG Data")
	FRPGData RPGData;

	UFUNCTION(BlueprintCallable, Category = "RPG Data")
	void SetRPGData(const FRPGData& NewRPGData);

	UFUNCTION()
	void Update();

	UFUNCTION()
	void LookAtTarget();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
