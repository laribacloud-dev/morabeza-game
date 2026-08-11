#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MORABEZAPlayerState.generated.h"

UCLASS()
class MORABEZA_API AMORABEZAPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    AMORABEZAPlayerState();

    UFUNCTION(BlueprintPure, Category = "Economy")
    int32 GetMoney() const { return Money; }

    UFUNCTION(BlueprintCallable, Category = "Economy")
    void AddMoney(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Economy")
    bool SpendMoney(int32 Amount);

    UFUNCTION(BlueprintPure, Category = "Progression")
    int32 GetReputation() const { return Reputation; }

    UFUNCTION(BlueprintCallable, Category = "Progression")
    void AddReputation(int32 Amount);

private:
    UPROPERTY(VisibleAnywhere, SaveGame, Category = "Economy")
    int32 Money = 500;

    UPROPERTY(VisibleAnywhere, SaveGame, Category = "Progression")
    int32 Reputation = 0;
};
