// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/TrainerCharacter.h"
#include "Main/KaijuKolosseumGameState.h"
#include "Gameplay/Actors/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ATrainerCharacter::ATrainerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1000.0f, 0.0f); // ...at this rotation rate

	//Create Spring Arm Component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = false;

	//Create Camera Component
	TamerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Tamer View"));
	TamerCam->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//Create Trigger Sphere
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
	SphereComp->SetupAttachment(RootComponent);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void ATrainerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrainerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrainerCharacter::Update()
{

	//LookAtTarget(); <---COMMENTING OUT until I find a quick way to call this. 
}

//Need to call this function once, no need for the tick function because this is the trainer character
void ATrainerCharacter::LookAtTarget()
{
	AKaijuKolosseumGameState* GameState = Cast<AKaijuKolosseumGameState>(GetWorld()->GetGameState());
	if (GameState)
	{
		if (GameState->CurrentGameState == EGameState::Overworld && RPGData.WKaiju)
		{

			bUseControllerRotationYaw = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), RPGData.WKaiju->GetActorLocation());
			GetController()->SetControlRotation(LookAtRotation);

		}
	}
	
}

void ATrainerCharacter::SetRPGData(const FRPGData& NewRPGData)
{
	RPGData = NewRPGData;
}


