#include "MORABEZADialogueComponent.h"

UMORABEZADialogueComponent::UMORABEZADialogueComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    DialogueLines.Add(
        FText::FromString(
            TEXT("Bem-vindo a Morabeza.")
        )
    );

    DialogueLines.Add(
        FText::FromString(
            TEXT("Tenho uma missão para ti.")
        )
    );

    DialogueLines.Add(
        FText::FromString(
            TEXT("Volta aqui quando estiveres preparado.")
        )
    );
}

void UMORABEZADialogueComponent::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE: Component started."
        )
    );
}

void UMORABEZADialogueComponent::StartDialogue()
{
    if (DialogueLines.Num() == 0)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA DIALOGUE: No dialogue lines configured."
            )
        );

        return;
    }

    CurrentLineIndex = 0;
    bDialogueActive = true;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE: Started."
        )
    );

    OnDialogueLineChanged.Broadcast(
        SpeakerName,
        DialogueLines[CurrentLineIndex]
    );
}

void UMORABEZADialogueComponent::AdvanceDialogue()
{
    if (!bDialogueActive)
    {
        return;
    }

    ++CurrentLineIndex;

    if (CurrentLineIndex >= DialogueLines.Num())
    {
        bDialogueActive = false;

        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA DIALOGUE: Finished."
            )
        );

        OnDialogueFinished.Broadcast();

        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE: Advancing to line %d."
        ),
        CurrentLineIndex
    );

    OnDialogueLineChanged.Broadcast(
        SpeakerName,
        DialogueLines[CurrentLineIndex]
    );
}
