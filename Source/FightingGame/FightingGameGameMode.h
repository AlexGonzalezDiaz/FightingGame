// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightingGameCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "FightingGameGameMode.generated.h"

//class UCharacterSelectData;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	VE_Default	UMETA(DisplayName = "Mannequin"),
	VE_Laboon	UMETA(DisplayName = "Laboon")
};


UCLASS(minimalapi)
class AFightingGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFightingGameGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items Database")
	class UCharacterSelectData* CharacterData;
	

protected:
	
	virtual void BeginPlay() override;
};



