// Fill out your copyright notice in the Description page of Project Settings.

#include "KaijuKolosseumGameState.h"
#include "Misc/Globals.h"
#include "Gameplay/Actors/FightingGameCharacter.h"
#include "Gameplay/Actors/TrainerCharacter.h"
#include "Main/Runners/LocalRunner.h"
#include "Gameplay/Controllers/KaijuPlayerController.h"
#include "Gameplay/Controllers/TrainerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"


AKaijuKolosseumGameState::AKaijuKolosseumGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKaijuKolosseumGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LocalRunner->FixedUpdate(DeltaTime);
}

void AKaijuKolosseumGameState::BeginPlay()
{
	Super::BeginPlay();
	
	// LOCAL RUNNER
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	LocalRunner = GetWorld()->SpawnActor<ALocalRunner>(ALocalRunner::StaticClass(), SpawnParams);

	//Spawn the tamer character
	RPGPlayer = GetWorld()->SpawnActor<ATrainerCharacter>(RPGData.Trainer, FVector(960.0,900.0, 0.0), FRotator::ZeroRotator);
	
	// CAMERA
	CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
	CameraActor->GetCameraComponent()->SetFieldOfView(54);
	const FVector NewCameraLocation = BattlePlayerTransform.GetRotation().RotateVector(FVector(200, 1080, 50)) + BattlePlayerTransform.GetLocation();
	CameraActor->SetActorLocation(NewCameraLocation);
	if (CameraActor)
	{
		if (const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(RPGPlayer);
		}
	}
	
	//FindPlayerStarts();

	////Set up the GameState on the fighting character
	//for (int i = 0; i < MaxPlayerObjects; i++)
	//{
	//	BattleData.MainPlayer[i]->GameState = this;
	//	BattleData.StartLocations[i].Z = Players[i]->PosZ;
	//	Players[i]->GroundLevel = Players[i]->PosZ;
	//}

	//AssignControllers(Players[1]);
	AssignControllers(nullptr,RPGPlayer);
	
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
		Players[i] = GetWorld()->SpawnActor<AFightingGameCharacter>(BattleData.PlayerList[0], BattleData.StartLocations[i], FRotator::ZeroRotator);
		Players[i]->PlayerIndex = i; //Setting player 1 and 2.
	}
	//Filling out the BattleData
	BattleData.MainPlayer[0] = Players[0];
	BattleData.MainPlayer[1] = Players[1];

}

void AKaijuKolosseumGameState::AssignControllers(AFightingGameCharacter* Player, ATrainerCharacter* Trainer)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is null in AssignControllers"));
		return;
	}

	// Get the existing player controller
	APlayerController* ExistingController = UGameplayStatics::GetPlayerController(World, 0);
	ATrainerController* TrainerController = Cast<ATrainerController>(ExistingController);

	if (TrainerController)
	{
		// Possess the trainer character with the existing controller
		TrainerController->Possess(Trainer);
		UE_LOG(LogTemp, Log, TEXT("Assigned existing controller ID %s to trainer"), *TrainerController->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find TrainerController for player index %d"), PlayerIndex);
	}
	//UWorld* World = GetWorld();
	//if (!World)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("World is null in AssignControllers"));
	//	return;
	//}

	//// Ensure we have a valid PlayerControllerClass
	//if (!PlayerControllerClass)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("PlayerControllerClass is not set. Please set it in the Blueprint."));
	//	return;
	//}

	// Spawn the Blueprint version of the player controller
	//FActorSpawnParameters SpawnParams;
	//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//AKaijuPlayerController* NewController = nullptr;
	//ATrainerController* TrainerController = World->SpawnActor<ATrainerController>(TrainerControllerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	//if (TrainerController)
	//{
		// Create a new ULocalPlayer for this controller
		//UGameInstance * GameInstance = GetGameInstance();
		//if (GameInstance)
		//{
		//	FString error;
		//	ULocalPlayer* NewLocalPlayer = GameInstance->CreateLocalPlayer(0, error , true);
		//	if (NewLocalPlayer)
		//	{
		//		//NewController->SetPlayer(NewLocalPlayer);
		//		TrainerController->SetPlayer(NewLocalPlayer);
		//		UE_LOG(LogTemp, Log, TEXT("Created LocalPlayer for Controller ID: %d"), PlayerIndex);
		//	}
		//	else
		//	{
		//		UE_LOG(LogTemp, Error, TEXT("Failed to create LocalPlayer for Controller ID: %d"), PlayerIndex);
		//	}
		//}

		// Possess the pawn with the new controller
		//NewController->Possess(Player);
		//TrainerController->Possess(Trainer);
		//TrainerController->SetViewTargetWithBlend(CameraActor);

		//UE_LOG(LogTemp, Log, TEXT("Assigned controller ID %s to player"), *Trainer->GetController()->GetName());
	//}
}

int AKaijuKolosseumGameState::GetLocalInputs(int Index) const
{
	//// Retrieve the player controller
	//if (const AKaijuPlayerController* Controller = Cast<AKaijuPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), Index)))
	//{
	//	if (IsValid(Controller))
	//	{
	//		if (Index == 0)
	//		{
	//			FString InputsString = FString::Printf(TEXT("%i"), Controller->Inputs);
	//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, InputsString);
	//		}
	//		if (Index == 1)
	//		{
	//			FString InputsString2 = FString::Printf(TEXT("%i"), Controller->Inputs);
	//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, InputsString2);
	//		}
	//		return Controller->Inputs;
	//	}
	//}

	return 0;
}

void AKaijuKolosseumGameState::UpdateState()
{
	//UpdateLocalInput() to find the inputs of p1 and p2 for future use
	//UpdateState should just only get the local inputs of p1. 
	//UpdateState(GetLocalInputs(0), GetLocalInputs(1));
}


void AKaijuKolosseumGameState::UpdateState(int32 P1Inputs, int32 P2Inputs)
{
	// Passing inputs by frame.
	Players[0]->Inputs = P1Inputs;
	Players[1]->Inputs = P2Inputs;
	// Updating the player character by frame.
	Players[0]->Update(); 
	Players[1]->Update();
}

void AKaijuKolosseumGameState::SwitchGameState(EGameState NewState)
{
	if (NewState == EGameState::Battle)
	{

	}
	else if (NewState == EGameState::Overworld)
	{

	}

}









