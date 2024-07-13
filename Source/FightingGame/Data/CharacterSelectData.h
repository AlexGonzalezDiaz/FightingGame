#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterSelectData.generated.h"

class AFightingGameCharacter; 

USTRUCT(BlueprintType)
struct FCharaSelectStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AFightingGameCharacter> CharacterBP;
};

/** Creating the player structure
**/
UCLASS()
class FIGHTINGGAME_API UCharacterSelectData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FCharaSelectStruct> characterSelectStruct;

};
