#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MORABEZAHUD.generated.h"

class UMORABEZAInteractionWidget;
class UMORABEZADialogueWidget;
class UMORABEZADialogueComponent;

UCLASS()
class MORABEZA_API AMORABEZAHUD : public AHUD
{
    GENERATED_BODY()

public:

    AMORABEZAHUD();

    void OpenDialogue(
        const FText& SpeakerName,
        const FText& DialogueText
    );

    void AdvanceDialogue();

    bool IsDialogueActive() const;

    void SetActiveDialogueComponent(
        UMORABEZADialogueComponent* DialogueComponent
    );

    UFUNCTION()
    void HandleDialogueLineChanged(
        const FText& Speaker,
        const FText& Text
    );

    UFUNCTION()
    void HandleDialogueFinished();

protected:

    virtual void BeginPlay() override;

private:

    UPROPERTY()
    TObjectPtr<UMORABEZAInteractionWidget> InteractionWidget;

    UPROPERTY()
    TObjectPtr<UMORABEZADialogueWidget> DialogueWidget;

    UPROPERTY()
    TObjectPtr<UMORABEZADialogueComponent> ActiveDialogueComponent;

    FText CurrentSpeaker;

    FText CurrentDialogue;

    bool bDialogueActive = false;
};
