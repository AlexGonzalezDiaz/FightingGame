// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameGameMode.h"
#include "FightingGameCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "CharacterSelectData.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFightingGameGameMode::AFightingGameGameMode()
{
    // Log a message when the game mode is constructed
    UE_LOG(LogTemp, Log, TEXT("FightingGameGameMode constructor called"));
	
}

void AFightingGameGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay of FightingGameMode"));
    
    getPlayerStartPoints();
}

void AFightingGameGameMode::spawnPlayers(TArray<APlayerStart*> arrayToPrint)
{

}

void AFightingGameGameMode::SpawnCharacterAtIndex(AActor* Actor, int32 Index)
{  
    if (CharacterData)
    {
        // Check if the index is valid
        if (Index >= 0 && Index < CharacterData->characterSelectStruct.Num())
        {
            // Get the blueprint class from the array
            TSubclassOf<AFightingGameCharacter> CharacterBP = CharacterData->characterSelectStruct[Index].CharacterBP;

            // Spawn the character
            if (CharacterBP)
            {
                FTransform SpawnXForm = Actor->GetActorTransform(); // Set your desired spawn location
                //FRotator SpawnRotation = Actor->GetActorRotation(); // Set your desired spawn rotation
                const FActorSpawnParameters SpawnParams;
                //AActor* NewCharacter = GetWorld()->SpawnActor<AActor>(CharacterBP, SpawnLocation, SpawnRotation);
                //if (NewCharacter)
                //{
                    // Optionally, you can do additional setup for the spawned character here
                //}
                if (UWorld* World = GetWorld())
                {
                    World->SpawnActor<AFightingGameCharacter>(CharacterBP, SpawnXForm, SpawnParams);
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Character blueprint is nullptr."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid index to spawn character."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Character is nullptr."));
    }
}

void AFightingGameGameMode::getPlayerStartPoints()
{
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), playerStartPoints); // Get all actors of type APlayerStart

    for (AActor* Actor : playerStartPoints)
    {
        APlayerStart* PlayerStart = Cast<APlayerStart>(Actor); // Cast to APlayerStart

        if (PlayerStart)
        {
            FString Tag = PlayerStart->PlayerStartTag.ToString(); // Get the tag of the player start

            // Compare the tag to determine if it's the one you're looking for
            if (Tag == "P1" || Tag == "P2")
            {
                // This player start has the tag you're looking for, handle it here
                // For example, you can store it in an array or directly use it to spawn a character

                SpawnCharacterAtIndex(Actor, 0);
                
            }
        }
    }
      

}
