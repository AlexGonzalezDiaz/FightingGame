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

	UPROPERTY(EditAnywhere)
	int32 maxPlayers;
	TArray<AActor*> currPlayers;
	TArray <AActor*> playerStartPoints;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFightingGameCharacter* player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFightingGameCharacter* player2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items Database")
	class UCharacterSelectData* CharacterData;



	// To link BP class and C++ code to avoid ConstructorHelpers
	UPROPERTY(EditDefaultsOnly, Category = "Default Player")
	TSubclassOf<AFightingGameCharacter> playerChara;

protected:
	
	void getPlayerStartPoints();
	void spawnPlayers(TArray<APlayerStart*> arrayToPrint);
	void SpawnCharacterAtIndex(AActor * Actor, int32 Index);
	virtual void BeginPlay() override;
};



