// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bitflags.generated.h"

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EInputFlags
{
	None = 0 UMETA(Hidden),
	INP_8 = 1 << 0 UMETA(DisplayName = "Up") // Up Input, to handle jump.
};

ENUM_CLASS_FLAGS(EInputFlags);