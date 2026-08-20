#include "MORABEZAInteractionWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

void UMORABEZAInteractionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA WIDGET: NativeConstruct started.")
    );

    /*
     * ============================================================
     * ROOT CANVAS
     * ============================================================
     */

    UCanvasPanel* Canvas =
        WidgetTree->ConstructWidget<UCanvasPanel>(
            UCanvasPanel::StaticClass()
        );

    WidgetTree->RootWidget = Canvas;

    Canvas->SetVisibility(
        ESlateVisibility::SelfHitTestInvisible
    );


    /*
     * ============================================================
     * INTERACTION TEXT
     * ============================================================
     */

    InteractionText =
        WidgetTree->ConstructWidget<UTextBlock>(
            UTextBlock::StaticClass()
        );

    Canvas->AddChild(InteractionText);

    InteractionText->SetText(
        FText::GetEmpty()
    );

    InteractionText->SetJustification(
        ETextJustify::Center
    );


    /*
     * ============================================================
     * LARGE, CLEAR DEBUG FONT
     * ============================================================
     */

    FSlateFontInfo FontInfo =
        InteractionText->GetFont();

    FontInfo.Size = 32;

    InteractionText->SetFont(
        FontInfo
    );


    /*
     * ============================================================
     * FULL-SCREEN CANVAS POSITION
     * ============================================================
     */

    UCanvasPanelSlot* CanvasSlot =
        Cast<UCanvasPanelSlot>(
            InteractionText->Slot
        );

    if (CanvasSlot)
    {
        /*
         * Center horizontally.
         */
        FAnchors Anchors;

        Anchors.Minimum =
            FVector2D(0.5f, 0.80f);

        Anchors.Maximum =
            FVector2D(0.5f, 0.80f);

        CanvasSlot->SetAnchors(
            Anchors
        );

        CanvasSlot->SetAlignment(
            FVector2D(0.5f, 0.5f)
        );

        CanvasSlot->SetPosition(
            FVector2D::ZeroVector
        );

        CanvasSlot->SetSize(
            FVector2D(800.0f, 80.0f)
        );
    }


    /*
     * ============================================================
     * START HIDDEN
     * ============================================================
     */

    InteractionText->SetVisibility(
        ESlateVisibility::Collapsed
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA WIDGET: NativeConstruct finished.")
    );
}


void UMORABEZAInteractionWidget::SetInteractionPrompt(
    const FText& Prompt
)
{
    if (!InteractionText)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA WIDGET: InteractionText is NULL."
            )
        );

        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA WIDGET: Prompt received = '%s'"
        ),
        *Prompt.ToString()
    );

    InteractionText->SetText(
        Prompt
    );

    if (Prompt.IsEmpty())
    {
        InteractionText->SetVisibility(
            ESlateVisibility::Collapsed
        );

        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA WIDGET: Prompt hidden."
            )
        );
    }
    else
    {
        InteractionText->SetVisibility(
            ESlateVisibility::HitTestInvisible
        );

        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA WIDGET: Prompt VISIBLE."
            )
        );
    }
}
