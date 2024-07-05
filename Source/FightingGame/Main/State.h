#pragma once

#include "CoreMinimal.h"
#include "Misc/Bitflags.h"
#include "StateMachineFG.h"
#include "State.generated.h"

class AFightingGameCharacter;
UENUM(BlueprintType)
enum class EEntryReq : uint8
{
	//Any prior state can transition
	None,
	Standing,
	Crouching,
	Jumping,

};

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Standing,
	Crouching,
	Jumping,
};


USTRUCT(BlueprintType)
struct FInputBitmask
{
	GENERATED_BODY()

	FInputBitmask()
	{
		InputFlag = None;
	};
	FInputBitmask(EInputFlags Input)
	{
		InputFlag = Input;
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "/Script/FightingGame.EInputFlags"))
	int InputFlag;
};

USTRUCT(BlueprintType)
struct FInputConditionList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FInputBitmask> InputCondition;
};


UCLASS(BlueprintType,Blueprintable)
class FIGHTINGGAME_API UState : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FName StateName;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	AFightingGameCharacter* Parent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FStateMachineFG StateMachine;

	UPROPERTY(EditAnywhere)
	EEntryReq EntryReq;

	UPROPERTY(EditAnywhere)
	TArray<FInputConditionList> InputConditionLists;

	UPROPERTY(EditAnywhere)
	EStateType StateType;

	UPROPERTY()
	bool FinishedState = false;

	UPROPERTY(BlueprintReadWrite)
	bool InitState = false;

	UFUNCTION(BlueprintNativeEvent)
	void Execute();

	UFUNCTION(BlueprintNativeEvent)
	bool ExitState();

	virtual void Execute_Implementation();
	virtual bool ExitState_Implementation();

private:
	void GetName();
};
