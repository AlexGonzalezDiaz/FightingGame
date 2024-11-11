// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/AICharacter.h"
#include "Main/KaijuKolosseumGameState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameplay/Actors/TrainerCharacter.h"
#include "Components/SphereComponent.h"
#include "Gameplay/Controllers/KaijuAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Trigger Sphere
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);

}


// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnOverlapBegin);
	AIController = Cast<AAIController>(GetController());
	if (!AIController)
		UE_LOG(LogTemp, Warning, TEXT("Failed to get AIController in BeginPlay."));
	GameState = Cast<AKaijuKolosseumGameState>(GetWorld()->GetGameState());
	if(!GameState)
		UE_LOG(LogTemp, Warning, TEXT("Failed to get GameState in BeginPlay."));
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtTarget();

}

void AAICharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TrainerChar = Cast<ATrainerCharacter>(OtherActor);

	if(TrainerChar)
	{
		//Lock onto the trainer
		FString ActorName = OtherActor->GetName();


		UpdateBlackBoard(TrainerChar);

	}
}

void AAICharacter::UpdateBlackBoard(ATrainerCharacter* Player)
{
	if (AIController)
	{
		UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
		if (BBComp)
		{
			BBComp->SetValueAsObject("TrainerCharacter", Player);
			BBComp->SetValueAsBool("IsPlayerInRange", true);
			//UE_LOG(LogTemp, Warning, TEXT("BB updated with player!"));
		}
	}

}

void AAICharacter::Update()
{
	//LookAtTarget();		
}

void AAICharacter::LookAtTarget()
{
	if (TrainerChar && AIController)
	{
		
		bUseControllerRotationYaw = true;
		//GetCharacterMovement()->bOrientRotationToMovement = false;
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TrainerChar->GetActorLocation());
		SetActorRotation(LookAtRotation);
	}

}

UBehaviorTree* AAICharacter::GetBehaviorTree() const
{
	return Tree;
}






