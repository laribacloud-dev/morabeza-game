#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MORABEZASaveGame.generated.h"

UCLASS()
class MORABEZA_API UMORABEZASaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Save")
    int32 Money = 500;

    UPROPERTY(BlueprintReadWrite, Category = "Save")
    int32 Reputation = 0;

    UPROPERTY(BlueprintReadWrite, Category = "Save")
    FVector PlayerLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite, Category = "Save")
    FRotator PlayerRotation = FRotator::ZeroRotator;

    UPROPERTY(BlueprintReadWrite, Category = "Save")
    FString CurrentMissionId;
};
