#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
//#include "State.h"
#include "Misc/Bitflags.h"
#include "StateData.generated.h"

class UState;

USTRUCT(BlueprintType)
struct FStateDataStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FName StateName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EInputFlags"))
	int InputFlag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStateFlags StateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStateFlags EntryStateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStateFlags ExitStateType;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UState> StateInfo;
};

UCLASS()
class FIGHTINGGAME_API UStateData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FStateDataStruct> StateDataStruct;
	
};