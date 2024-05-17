// Fill out your copyright notice in the Description page of Project Settings.


#include "KaijuKolosseumState.h"
#include "KaijuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

AKaijuKolosseumState::AKaijuKolosseumState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AKaijuKolosseumState::BeginPlay()
{
	Super::BeginPlay();

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
	
}
