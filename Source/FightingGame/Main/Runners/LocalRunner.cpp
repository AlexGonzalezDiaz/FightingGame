// Fill out your copyright notice in the Description page of Project Settings.


#include "Main/Runners/LocalRunner.h"
#include "Main/KaijuKolosseumGameState.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ALocalRunner::ALocalRunner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;
	//Consider initializing the variables in the constructor instead
}

//Main point of the class is to run all the float time in fixed frames.
//Very important for deterministic gameplay. All other functions will be to help out this function
// *** Gets called in the KaijuKolosseumGameState Tick();

void ALocalRunner::FixedUpdate(float DeltaTime)
{

	if (InState)
	{
		CurrTime += DeltaTime;
		while (CurrTime >= OneFrame)
		{
			InState->UpdateState();
			CurrTime -= OneFrame; // Reset the CurrTime to evaluate the next frame.
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("In state not valid"))
	}
}


void ALocalRunner::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundFighterGameStates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKaijuKolosseumGameState::StaticClass(), FoundFighterGameStates);
	if (FoundFighterGameStates.Num() > 0) {
		InState = Cast<AKaijuKolosseumGameState>(FoundFighterGameStates[0]);
	}
	UE_LOG(LogTemp, Warning, TEXT("Instate is: %s"), *InState->GetName());
}


