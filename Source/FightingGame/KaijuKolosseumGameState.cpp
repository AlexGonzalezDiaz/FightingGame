// Fill out your copyright notice in the Description page of Project Settings.

#include "KaijuKolosseumGameState.h"
#include "FightingGameCharacter.h"
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
	
	FTransform BattleSceneTransform;

	CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
	CameraActor->GetCameraComponent()->SetFieldOfView(54);

	const FVector NewCameraLocation = BattleSceneTransform.GetRotation().RotateVector(FVector(0, 1080, 175)) + BattleSceneTransform.GetLocation();

	CameraActor->SetActorLocation(NewCameraLocation);
	if (CameraActor)
	{
		if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(CameraActor);
		}
	}
	
	FindPlayerStarts();

}

void AKaijuKolosseumGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateState(GetLocalInputs(0),0);

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

void AKaijuKolosseumGameState::Init()
{
	
	for (int i = 0; i < MaxPlayerObjects; i++)
	{
		FTransform PlayerTransform(BattleData.StartLocations[i]);

		Players[i] = GetWorld()->SpawnActor<AFightingGameCharacter>(BattleData.PlayerList[0],PlayerTransform);
		Players[i]->PlayerIndex = i; //Setting player 1 and 2.

	}
	
	//Filling out the BattleData
	BattleData.MainPlayer[0] = Players[0];
	BattleData.MainPlayer[1] = Players[1];

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

			// Compare the tag to determine if it's the one you're looking for
			if (Tag == "P1")
			{
				//For the rotation to match up, consider looking how to customize the player start positions. 
				BattleData.StartLocations[0] = FVector(PlayerStart->GetActorLocation().X, PlayerStart->GetActorLocation().Y, 0.0);
				
			}
			if (Tag == "P2")
			{
				BattleData.StartLocations[1] = FVector(PlayerStart->GetActorLocation().X, PlayerStart->GetActorLocation().Y, 0.0);

			}
		}
	}

	Init();
}


void AKaijuKolosseumGameState::UpdateState(int32 P1Inputs, int32 P2Inputs)
{

	BattleData.MainPlayer[0]->Inputs = P1Inputs;

	FString InputsString = FString::Printf(TEXT("Inputs: %i"), P1Inputs);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, InputsString);
}





