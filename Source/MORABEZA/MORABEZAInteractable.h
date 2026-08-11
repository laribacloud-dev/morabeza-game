#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MORABEZAInteractable.generated.h"

UINTERFACE(BlueprintType)
class MORABEZA_API UMORABEZAInteractable : public UInterface
{
    GENERATED_BODY()
};

class MORABEZA_API IMORABEZAInteractable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Interact(AActor* Interactor);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    FText GetInteractionPrompt() const;
};
