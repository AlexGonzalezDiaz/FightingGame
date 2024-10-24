// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/AICharacter.h"
#include "Main/KaijuKolosseumGameState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Gameplay/Actors/TrainerCharacter.h"
#include "Components/SphereComponent.h"
#include "Gameplay/AI/KaijuAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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
}

void AAICharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATrainerCharacter* Trainer = Cast<ATrainerCharacter>(OtherActor);

	if(Trainer)
	{
		//Lock onto the trainer
		FString ActorName = OtherActor->GetName();
		FString Message = FString::Printf(TEXT("Overlapped with: %s"), *ActorName);


		UpdateBlackBoard(Trainer);

	}
}

void AAICharacter::UpdateBlackBoard(ATrainerCharacter* Player)
{
	if (AIController)
	{
		UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
		if (BBComp)
		{
			BBComp->SetValueAsObject("PlayerDetected", Player);
			BBComp->SetValueAsBool("IsPlayerInRange", true);
			UE_LOG(LogTemp, Warning, TEXT("BB updated with player!"));
		}
	}

}

void AAICharacter::LookAtTarget(ATrainerCharacter* NewTarget)
{

}

UBehaviorTree* AAICharacter::GetBehaviorTree() const
{
	return Tree;
}



