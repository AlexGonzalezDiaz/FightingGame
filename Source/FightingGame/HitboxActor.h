// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitboxActor.generated.h"


UENUM(BlueprintType)
enum class EHitboxEnum : uint8
{
	HB_PROXIMITY	UMETA(DisplayName = "Proximity"),
	HB_STRIKE		UMETA(DisplayName = "Strike"),
	HB_HURTBOX		UMETA(DisplayName = "Hurtbox") // What goes around the character
};

UCLASS()
class FIGHTINGGAME_API AHitboxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitboxActor();

	//Notify the HitboxActorBP class instance that the hitbox is ready to be drawn
	UFUNCTION(BlueprintCallable)
	void TriggerVisualizeHitbox();

	//Draw the hitbox to the screen to visualize it 
	UFUNCTION(BlueprintImplementableEvent)
	void VisualizeHitbox();

	//The hitbox enum instance.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	EHitboxEnum hitboxType;

	//The damage the hitbox will do.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	float hitboxDamage;

	//The location to spawn the hitbox.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	FVector hitboxLocation;

	//The rotation to spawn the hitbox.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	FVector hitboxRotation;

	//The amount of distance to launch the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	float launchDistance;

	//The amount of distance to launch the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	float hitStunTime;

protected:

public:	

};
