// Fill out your copyright notice in the Description page of Project Settings.

#include "KaijuKolosseumGameState.h"
#include "FightingGameCharacter.h"
#include "Main/Runners/LocalRunner.h"
#include "KaijuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"


AKaijuKolosseumGameState::AKaijuKolosseumGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKaijuKolosseumGameState::BeginPlay()
{
	Super::BeginPlay();
	
	// LOCAL RUNNER
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	LocalRunner = GetWorld()->SpawnActor<ALocalRunner>(ALocalRunner::StaticClass(), SpawnParams);

	// CAMERA
	CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
	CameraActor->GetCameraComponent()->SetFieldOfView(54);
	const FVector NewCameraLocation = BattlePlayerTransform.GetRotation().RotateVector(FVector(50, 1080, 175)) + BattlePlayerTransform.GetLocation();
	CameraActor->SetActorLocation(NewCameraLocation);
	if (CameraActor)
	{
		if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(CameraActor);
		}
	}
	
	FindPlayerStarts();

	//Set up the GameState on the fighting character
	for (int i = 0; i < 2; i++)
	{
		BattleData.MainPlayer[i]->GameState = this;
		BattleData.StartLocations[i].Z = Players[i]->PosZ;
		UE_LOG(LogTemp, Warning, TEXT("StartLocations after %s"), *BattleData.StartLocations[i].ToString());
		Players[i]->GroundLevel = Players[i]->PosZ;
	}
	
}

void AKaijuKolosseumGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LocalRunner->FixedUpdate(DeltaTime);

}

int AKaijuKolosseumGameState::GetLocalInputs(int Index) const
{
	// Retrieve the player controller
	if (const AKaijuPlayerController* Controller = Cast<AKaijuPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), Index)))
	{
		if (IsValid(Controller))
		{
			return Controller->Inputs;
		}
	}

	return 0;
}

void AKaijuKolosseumGameState::FindPlayerStarts()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), BattleData.playerStartPoints); // Get all actors of type APlayerStart

	for (AActor* Actor : BattleData.playerStartPoints)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(Actor); // Cast to APlayerStart

		if (PlayerStart)
		{
			FString Tag = PlayerStart->PlayerStartTag.ToString(); // Get the tag of the player start
			int32 ActorLocX = static_cast<int32>(PlayerStart->GetActorLocation().X);
			int32 ActorLocY = static_cast<int32>(PlayerStart->GetActorLocation().Y);
			int32 ActorLocZ = static_cast<int32>(PlayerStart->GetActorLocation().Z);
			ActorLocZ = 0;
			// Compare the tag to determine if it's the one you're looking for
			if (Tag == "P1")
			{
				//For the rotation to match up, consider looking how to customize the player start positions. 
				BattleData.StartLocations[0] = FVector(ActorLocX, ActorLocY, ActorLocZ);
				
			}
			if (Tag == "P2")
			{
				BattleData.StartLocations[1] = FVector(ActorLocX, ActorLocY, ActorLocZ);

			}
		}
	}

	Init();
}

void AKaijuKolosseumGameState::Init()
{
	
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		//BattleData.StartLocations[i].Z = 0;
		Players[i] = GetWorld()->SpawnActor<AFightingGameCharacter>(BattleData.PlayerList[0], BattleData.StartLocations[i], FRotator::ZeroRotator);
		Players[i]->PlayerIndex = i; //Setting player 1 and 2.
		//BattleData.StartLocations[i].Z = PlayerTransform.GetLocation().Z;
	}

	UE_LOG(LogTemp, Warning, TEXT("PosZ in GameState Init() %i"), Players[0]->PosZ);
	//Filling out the BattleData
	BattleData.MainPlayer[0] = Players[0];
	BattleData.MainPlayer[1] = Players[1];

}


void AKaijuKolosseumGameState::UpdateState(int32 P1Inputs, int32 P2Inputs)
{
	// Passing inputs by frame.
	BattleData.MainPlayer[0]->Inputs = P1Inputs;
	// Updating the player character by frame.
	BattleData.MainPlayer[0]->Update(); 

	FString InputsString = FString::Printf(TEXT("Inputs: %i"), P1Inputs);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, InputsString);
}

void AKaijuKolosseumGameState::UpdateState()
{
	//UpdateLocalInput() to find the inputs of p1 and p2 for future use
	//UpdateState should just only get the local inputs of p1. 
	UpdateState(GetLocalInputs(0), 0);
}






