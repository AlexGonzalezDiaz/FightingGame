
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KaijuAIController.generated.h"

UCLASS()
class FIGHTINGGAME_API AKaijuAIController : public AAIController
{
	GENERATED_BODY()

public:
//~~~~~ FUNCTIONS ~~~~~//
	explicit AKaijuAIController(FObjectInitializer const& ObjectInitializer);

	void OnPlayerPressedInteractButton();

//~~~~~ FUNCTIONS ~~~~~//

//~~~~~ VARIABLES ~~~~~//

UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PlayerPressedButtonKey = "PlayerPressedButton";

//~~~~~ VARIABLES ~~~~~//

protected:
//~~~~~ FUNCTIONS ~~~~~//

	void OnPossess(APawn* InPawn) override;

//~~~~~ FUNCTIONS ~~~~~//

//~~~~~ VARIABLES ~~~~~//

//~~~~~ VARIABLES ~~~~~//
	
};
