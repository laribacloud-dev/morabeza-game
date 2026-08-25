#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MORABEZAGameMode.generated.h"

UCLASS()
class MORABEZA_API AMORABEZAGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMORABEZAGameMode();

protected:
    virtual void BeginPlay() override;

private:
    void SpawnTestContact();
};
