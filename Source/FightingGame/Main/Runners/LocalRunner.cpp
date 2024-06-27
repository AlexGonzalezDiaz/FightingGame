// Fill out your copyright notice in the Description page of Project Settings.


#include "Main/Runners/LocalRunner.h"

// Sets default values
ALocalRunner::ALocalRunner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Consider initializing the variables in the constructor instead
}

// Called every frame
void ALocalRunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Converting the seconds to whole integers
	AccumulatedTime += FMath::FloorToInt(DeltaTime * 1000);

	while (AccumulatedTime >= FixedTimeStep)
	{
		FixedUpdate();
		AccumulatedTime -= FixedTimeStep;
	}
}

void ALocalRunner::FixedUpdate()
{
}

