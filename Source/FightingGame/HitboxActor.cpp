// Fill out your copyright notice in the Description page of Project Settings.


#include "HitboxActor.h"

// Sets default values
AHitboxActor::AHitboxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	launchDistance = 0.0f;
	hitStunTime = 0.0f;
	pushbackDistance = 0.0f;
	isLaunched = false;

}

void AHitboxActor::TriggerVisualizeHitbox()
{
	VisualizeHitbox();
}




