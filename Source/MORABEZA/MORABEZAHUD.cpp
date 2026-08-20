#include "MORABEZAHUD.h"

#include "MORABEZAInteractionWidget.h"
#include "MORABEZADialogueWidget.h"
#include "MORABEZACharacter.h"
#include "MORABEZAInteractionComponent.h"
#include "Dialogue/MORABEZADialogueComponent.h"

#include "GameFramework/PlayerController.h"

AMORABEZAHUD::AMORABEZAHUD()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMORABEZAHUD::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController =
        GetOwningPlayerController();

    if (!PlayerController)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("MORABEZA HUD: No PlayerController found.")
        );

        return;
    }

    /*
     * ============================================================
     * INTERACTION WIDGET
     * ============================================================
     */

    InteractionWidget =
        CreateWidget<UMORABEZAInteractionWidget>(
            PlayerController,
            UMORABEZAInteractionWidget::StaticClass()
        );

    if (InteractionWidget)
    {
        InteractionWidget->AddToViewport(100);

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("MORABEZA HUD: InteractionWidget created.")
        );
    }

    /*
     * ============================================================
     * DIALOGUE WIDGET
     * ============================================================
     *
     * Dialogue is rendered by the HUD.
     *
     * The ContactActor only owns/triggers the dialogue component.
     * The HUD receives the dialogue line and displays it here.
     */

    DialogueWidget =
        CreateWidget<UMORABEZADialogueWidget>(
            PlayerController,
            UMORABEZADialogueWidget::StaticClass()
        );

    if (DialogueWidget)
    {
        DialogueWidget->AddToViewport(1000);

        DialogueWidget->SetVisibility(
            ESlateVisibility::Collapsed
        );

        DialogueWidget->SetRenderOpacity(1.0f);

        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA HUD: DialogueWidget created at Z=1000."
            )
        );
    }
    else
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA HUD: FAILED to create DialogueWidget."
            )
        );
    }

    /*
     * ============================================================
     * GAME INPUT MODE
     * ============================================================
     */

    FInputModeGameOnly InputMode;

    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;

    /*
     * ============================================================
     * CONNECT INTERACTION COMPONENT
     * ============================================================
     */

    AMORABEZACharacter* Character =
        Cast<AMORABEZACharacter>(
            PlayerController->GetPawn()
        );

    if (!Character)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA HUD: Player character not available."
            )
        );

        return;
    }

    UMORABEZAInteractionComponent* InteractionComponent =
        Character->FindComponentByClass<
            UMORABEZAInteractionComponent
        >();

    if (!InteractionComponent)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA HUD: InteractionComponent not found."
            )
        );

        return;
    }

    if (InteractionWidget)
    {
        InteractionComponent->OnPromptChanged.AddDynamic(
            InteractionWidget,
            &UMORABEZAInteractionWidget::SetInteractionPrompt
        );
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA HUD: Interaction prompt connected."
        )
    );
}

void AMORABEZAHUD::OpenDialogue(
    const FText& SpeakerName,
    const FText& DialogueText
)
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE: OpenDialogue() called."
        )
    );

    if (!DialogueWidget)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA DIALOGUE: DialogueWidget unavailable."
            )
        );

        return;
    }

    /*
     * ============================================================
     * STORE CURRENT LINE
     * ============================================================
     */

    CurrentSpeaker = SpeakerName;
    CurrentDialogue = DialogueText;

    /*
     * ============================================================
     * ACTIVATE DIALOGUE
     * ============================================================
     */

    bDialogueActive = true;

    /*
     * ============================================================
     * SHOW DIALOGUE
     * ============================================================
     */

    DialogueWidget->SetVisibility(
        ESlateVisibility::Visible
    );

    DialogueWidget->SetRenderOpacity(1.0f);

    DialogueWidget->ShowDialogue(
        CurrentSpeaker,
        CurrentDialogue
    );

    /*
     * ============================================================
     * HIDE INTERACTION PROMPT
     * ============================================================
     */

    if (InteractionWidget)
    {
        InteractionWidget->SetVisibility(
            ESlateVisibility::Collapsed
        );
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE: OPEN - Speaker=%s Text=%s"
        ),
        *SpeakerName.ToString(),
        *DialogueText.ToString()
    );
}

void AMORABEZAHUD::SetActiveDialogueComponent(
    UMORABEZADialogueComponent* DialogueComponent
)
{
    /*
     * IMPORTANT:
     *
     * Assigning a component does NOT mean dialogue has started.
     *
     * Dialogue becomes active only when the component broadcasts
     * its first dialogue line through OpenDialogue().
     */

    ActiveDialogueComponent =
        DialogueComponent;

    bDialogueActive = false;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA HUD: Active dialogue component assigned: %s"
        ),
        DialogueComponent
            ? *DialogueComponent->GetName()
            : TEXT("NONE")
    );
}

void AMORABEZAHUD::AdvanceDialogue()
{
    if (!bDialogueActive)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA HUD: AdvanceDialogue ignored - no active dialogue."
            )
        );

        return;
    }

    if (ActiveDialogueComponent)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA HUD: Advancing active dialogue."
            )
        );

        ActiveDialogueComponent->AdvanceDialogue();

        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA HUD: No active dialogue component."
        )
    );
}

void AMORABEZAHUD::HandleDialogueLineChanged(
    const FText& Speaker,
    const FText& Text
)
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA HUD: Dialogue line received."
        )
    );

    OpenDialogue(
        Speaker,
        Text
    );
}

void AMORABEZAHUD::HandleDialogueFinished()
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE: Finished."
        )
    );

    /*
     * ============================================================
     * RESET DIALOGUE STATE
     * ============================================================
     */

    bDialogueActive = false;

    ActiveDialogueComponent = nullptr;

    /*
     * ============================================================
     * HIDE DIALOGUE
     * ============================================================
     */

    if (DialogueWidget)
    {
        DialogueWidget->HideDialogue();

        DialogueWidget->SetVisibility(
            ESlateVisibility::Collapsed
        );

        DialogueWidget->SetRenderOpacity(1.0f);
    }

    /*
     * ============================================================
     * RESTORE INTERACTION PROMPT
     * ============================================================
     */

    if (InteractionWidget)
    {
        InteractionWidget->SetVisibility(
            ESlateVisibility::Visible
        );
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE: CLOSED."
        )
    );
}

bool AMORABEZAHUD::IsDialogueActive() const
{
    return bDialogueActive;
}