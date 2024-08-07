// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "FightingGameGameMode.generated.h"


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



