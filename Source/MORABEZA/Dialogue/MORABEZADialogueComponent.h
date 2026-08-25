#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MORABEZADialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FMORABEZADialogueLineChanged,
    const FText&,
    Speaker,
    const FText&,
    Text
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
    FMORABEZADialogueFinished
);

UCLASS(
    ClassGroup=(MORABEZA),
    BlueprintType,
    meta=(BlueprintSpawnableComponent)
)
class MORABEZA_API UMORABEZADialogueComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMORABEZADialogueComponent();

    UFUNCTION(BlueprintCallable, Category="Dialogue")
    void StartDialogue();

    UFUNCTION(BlueprintCallable, Category="Dialogue")
    void AdvanceDialogue();

    UFUNCTION(BlueprintPure, Category="Dialogue")
    bool IsDialogueActive() const
    {
        return bDialogueActive;
    }

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category="Dialogue"
    )
    FText SpeakerName = FText::FromString(TEXT("Test Contact"));

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category="Dialogue"
    )
    TArray<FText> DialogueLines;

    UPROPERTY(BlueprintAssignable, Category="Dialogue")
    FMORABEZADialogueLineChanged OnDialogueLineChanged;

    UPROPERTY(BlueprintAssignable, Category="Dialogue")
    FMORABEZADialogueFinished OnDialogueFinished;

protected:
    virtual void BeginPlay() override;

private:
    int32 CurrentLineIndex = 0;

    bool bDialogueActive = false;
};
