#include "MORABEZAInteractionWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

TSharedRef<SWidget> UMORABEZAInteractionWidget::RebuildWidget()
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA WIDGET: RebuildWidget START")
    );

    UCanvasPanel* Canvas =
        WidgetTree->ConstructWidget<UCanvasPanel>(
            UCanvasPanel::StaticClass(),
            TEXT("InteractionRootCanvas")
        );

    WidgetTree->RootWidget = Canvas;

    UBorder* Panel =
        WidgetTree->ConstructWidget<UBorder>(
            UBorder::StaticClass(),
            TEXT("InteractionPanel")
        );

    Canvas->AddChild(Panel);

    Panel->SetBrushColor(
        FLinearColor(
            0.02f,
            0.02f,
            0.02f,
            0.95f
        )
    );

    Panel->SetPadding(
        FMargin(
            24.0f,
            14.0f
        )
    );

    UCanvasPanelSlot* PanelSlot =
        Cast<UCanvasPanelSlot>(
            Panel->Slot
        );

    if (PanelSlot)
    {
        PanelSlot->SetAnchors(
            FAnchors(
                0.5f,
                0.78f,
                0.5f,
                0.78f
            )
        );

        PanelSlot->SetAlignment(
            FVector2D(
                0.5f,
                0.5f
            )
        );

        PanelSlot->SetPosition(
            FVector2D::ZeroVector
        );

        PanelSlot->SetSize(
            FVector2D(
                650.0f,
                90.0f
            )
        );
    }

    InteractionText =
        WidgetTree->ConstructWidget<UTextBlock>(
            UTextBlock::StaticClass(),
            TEXT("InteractionText")
        );

    Panel->SetContent(
        InteractionText
    );

    InteractionText->SetText(
        FText::FromString(
            TEXT("[E] Falar com Test Contact")
        )
    );

    InteractionText->SetJustification(
        ETextJustify::Center
    );

    FSlateFontInfo FontInfo =
        InteractionText->GetFont();

    FontInfo.Size = 32;

    InteractionText->SetFont(
        FontInfo
    );

    InteractionText->SetColorAndOpacity(
        FSlateColor(
            FLinearColor(
                1.0f,
                1.0f,
                1.0f,
                1.0f
            )
        )
    );

    InteractionText->SetVisibility(
        ESlateVisibility::Visible
    );

    Panel->SetVisibility(
        ESlateVisibility::Visible
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA WIDGET: Interaction tree constructed")
    );

    TSharedRef<SWidget> Result =
        Super::RebuildWidget();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA WIDGET: RebuildWidget COMPLETE")
    );

    return Result;
}

void UMORABEZAInteractionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SetVisibility(
        ESlateVisibility::Visible
    );

    SetRenderOpacity(
        1.0f
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA WIDGET: NativeConstruct COMPLETE")
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
            TEXT("MORABEZA WIDGET: InteractionText is NULL.")
        );

        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA WIDGET: Prompt received = '%s'"),
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
            TEXT("MORABEZA WIDGET: Prompt COLLAPSED")
        );

        return;
    }

    SetVisibility(
        ESlateVisibility::Visible
    );

    SetRenderOpacity(
        1.0f
    );

    InteractionText->SetVisibility(
        ESlateVisibility::Visible
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA WIDGET: Prompt VISIBLE")
    );
}
