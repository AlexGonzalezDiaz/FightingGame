// Fill out your copyright notice in the Description page of Project Settings.


#include "KaijuMovementComponent.h"

void UKaijuMovementComponent::JumpOff(AActor* MovementBaseActor)
{
	if (!bPerformingJumpOff)
	{
		bPerformingJumpOff = true;
		if (CharacterOwner)
		{
			const float MaxSpeed = GetMaxSpeed() * 0.85f;
			/*Velocity += MaxSpeed * GetBestDirectionOffActor(MovementBaseActor);*/
			/*if (Velocity.Size2D() > MaxSpeed)
			{
				Velocity = MaxSpeed * Velocity.GetSafeNormal();
			}*/
			Velocity.Z = JumpOffJumpZFactor * JumpZVelocity;
			SetMovementMode(MOVE_Falling);
		}
		bPerformingJumpOff = false;
	}
}

UKaijuMovementComponent::UKaijuMovementComponent()
{
}
