#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MORABEZAInteractionWidget.generated.h"

class UTextBlock;

UCLASS()
class MORABEZA_API UMORABEZAInteractionWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION()
    void SetInteractionPrompt(const FText& Prompt);

protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY()
    TObjectPtr<UTextBlock> InteractionText;
};
