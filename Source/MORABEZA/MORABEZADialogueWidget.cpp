#include "MORABEZADialogueWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/Spacer.h"

UMORABEZADialogueWidget::UMORABEZADialogueWidget(
    const FObjectInitializer& ObjectInitializer
)
    : Super(ObjectInitializer)
{
}

TSharedRef<SWidget> UMORABEZADialogueWidget::RebuildWidget()
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA DIALOGUE WIDGET: RebuildWidget START")
    );

    RootCanvas =
        WidgetTree->ConstructWidget<UCanvasPanel>(
            UCanvasPanel::StaticClass(),
            TEXT("DialogueRootCanvas")
        );

    WidgetTree->RootWidget =
        RootCanvas;

    DialoguePanel =
        WidgetTree->ConstructWidget<UBorder>(
            UBorder::StaticClass(),
            TEXT("DialoguePanel")
        );

    RootCanvas->AddChild(
        DialoguePanel
    );

    UCanvasPanelSlot* PanelSlot =
        Cast<UCanvasPanelSlot>(
            DialoguePanel->Slot
        );

    if (PanelSlot)
    {
        PanelSlot->SetAnchors(
            FAnchors(
                0.10f,
                0.68f,
                0.90f,
                0.92f
            )
        );

        PanelSlot->SetOffsets(
            FMargin(
                0.0f
            )
        );

        PanelSlot->SetAlignment(
            FVector2D(
                0.0f,
                0.0f
            )
        );
    }

    DialoguePanel->SetBrushColor(
        FLinearColor(
            0.015f,
            0.015f,
            0.015f,
            0.96f
        )
    );

    DialoguePanel->SetPadding(
        FMargin(
            35.0f,
            25.0f,
            35.0f,
            25.0f
        )
    );

    DialogueContent =
        WidgetTree->ConstructWidget<UVerticalBox>(
            UVerticalBox::StaticClass(),
            TEXT("DialogueContent")
        );

    DialoguePanel->SetContent(
        DialogueContent
    );

    SpeakerText =
        WidgetTree->ConstructWidget<UTextBlock>(
            UTextBlock::StaticClass(),
            TEXT("SpeakerText")
        );

    SpeakerText->SetText(
        FText::FromString(
            TEXT("Test Contact")
        )
    );

    SpeakerText->SetColorAndOpacity(
        FSlateColor(
            FLinearColor(
                1.0f,
                0.85f,
                0.20f,
                1.0f
            )
        )
    );

    FSlateFontInfo SpeakerFont =
        SpeakerText->GetFont();

    SpeakerFont.Size = 28;

    SpeakerText->SetFont(
        SpeakerFont
    );

    SpeakerText->SetAutoWrapText(
        true
    );

    DialogueContent->AddChildToVerticalBox(
        SpeakerText
    );

    USpacer* Spacer =
        WidgetTree->ConstructWidget<USpacer>(
            USpacer::StaticClass(),
            TEXT("DialogueSpacer")
        );

    Spacer->SetSize(
        FVector2D(
            1.0f,
            15.0f
        )
    );

    DialogueContent->AddChildToVerticalBox(
        Spacer
    );

    DialogueText =
        WidgetTree->ConstructWidget<UTextBlock>(
            UTextBlock::StaticClass(),
            TEXT("DialogueText")
        );

    DialogueText->SetText(
        FText::FromString(
            TEXT("Bem-vindo a Morabeza.")
        )
    );

    DialogueText->SetColorAndOpacity(
        FSlateColor(
            FLinearColor(
                1.0f,
                1.0f,
                1.0f,
                1.0f
            )
        )
    );

    FSlateFontInfo DialogueFont =
        DialogueText->GetFont();

    DialogueFont.Size = 24;

    DialogueText->SetFont(
        DialogueFont
    );

    DialogueText->SetAutoWrapText(
        true
    );

    DialogueContent->AddChildToVerticalBox(
        DialogueText
    );

    RootCanvas->SetVisibility(
        ESlateVisibility::Visible
    );

    DialoguePanel->SetVisibility(
        ESlateVisibility::Visible
    );

    DialogueContent->SetVisibility(
        ESlateVisibility::Visible
    );

    SpeakerText->SetVisibility(
        ESlateVisibility::Visible
    );

    DialogueText->SetVisibility(
        ESlateVisibility::Visible
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA DIALOGUE WIDGET: Dialogue tree constructed")
    );

    TSharedRef<SWidget> Result =
        Super::RebuildWidget();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA DIALOGUE WIDGET: RebuildWidget COMPLETE")
    );

    return Result;
}

void UMORABEZADialogueWidget::NativeConstruct()
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
        TEXT("MORABEZA DIALOGUE WIDGET: NativeConstruct COMPLETE")
    );
}

void UMORABEZADialogueWidget::ShowDialogue(
    const FText& SpeakerName,
    const FText& InDialogueText
)
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA DIALOGUE WIDGET: SHOW DIALOGUE")
    );

    if (
        !RootCanvas ||
        !DialoguePanel ||
        !DialogueContent ||
        !SpeakerText ||
        !DialogueText
    )
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("MORABEZA DIALOGUE WIDGET: INVALID WIDGET COMPONENTS")
        );

        return;
    }

    SpeakerText->SetText(
        SpeakerName
    );

    DialogueText->SetText(
        InDialogueText
    );

    SetVisibility(
        ESlateVisibility::Visible
    );

    SetRenderOpacity(
        1.0f
    );

    RootCanvas->SetVisibility(
        ESlateVisibility::Visible
    );

    DialoguePanel->SetVisibility(
        ESlateVisibility::Visible
    );

    DialogueContent->SetVisibility(
        ESlateVisibility::Visible
    );

    SpeakerText->SetVisibility(
        ESlateVisibility::Visible
    );

    DialogueText->SetVisibility(
        ESlateVisibility::Visible
    );

    InvalidateLayoutAndVolatility();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE WIDGET: Speaker=%s Text=%s"
        ),
        *SpeakerName.ToString(),
        *InDialogueText.ToString()
    );
}

void UMORABEZADialogueWidget::HideDialogue()
{
    SetVisibility(
        ESlateVisibility::Collapsed
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA DIALOGUE WIDGET: HIDDEN"
        )
    );
}
