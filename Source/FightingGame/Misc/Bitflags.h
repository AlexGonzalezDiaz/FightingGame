// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bitflags.generated.h"

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EInputFlags
{
	None = 0 UMETA(DisplayName = "None"),
	INP_8 = 1 << 0 UMETA(DisplayName = "Up"), // Up Input, to handle jump.
    INP_6 = 1 << 1 UMETA(DisplayName = "Forward") // Move direction toward player
};

ENUM_CLASS_FLAGS(EInputFlags);

UENUM(BlueprintType)
enum class EStateFlags : uint8
{
    None UMETA(DisplayName = "None"),
    Idle UMETA(DisplayName = "Idle"),
    Jump UMETA(DisplayName = "Jump"),
    Forward UMETA(DisplayName = "Move Forward")

};
