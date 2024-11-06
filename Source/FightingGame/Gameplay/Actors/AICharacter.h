// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AICharacter.generated.h"

class ATrainerCharacter;
class AKaijuAIController;
class AKaijuKolosseumGameState;

UCLASS()
class FIGHTINGGAME_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:	

	// Sets default values for this character's properties
	AAICharacter();	

	UPROPERTY(EditAnywhere)
	AKaijuKolosseumGameState* GameState;

	UPROPERTY(EditAnywhere)
	ATrainerCharacter* TrainerChar;

	UFUNCTION()
	UBehaviorTree* GetBehaviorTree() const;

	UFUNCTION()
	void UpdateBlackBoard(ATrainerCharacter* Player);

	UFUNCTION()
	void Update();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComp;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void LookAtTarget(ATrainerCharacter* Target);

private:
	UPROPERTY()
	AAIController* AIController;

};
