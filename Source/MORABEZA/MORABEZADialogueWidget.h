#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MORABEZADialogueWidget.generated.h"

class UCanvasPanel;
class UBorder;
class UVerticalBox;
class UTextBlock;

UCLASS()
class MORABEZA_API UMORABEZADialogueWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UMORABEZADialogueWidget(
        const FObjectInitializer& ObjectInitializer
    );

    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable, Category="Dialogue")
    void ShowDialogue(
        const FText& SpeakerName,
        const FText& InDialogueText
    );

    UFUNCTION(BlueprintCallable, Category="Dialogue")
    void HideDialogue();

private:

    UPROPERTY()
    TObjectPtr<UCanvasPanel> RootCanvas;

    UPROPERTY()
    TObjectPtr<UBorder> DialoguePanel;

    UPROPERTY()
    TObjectPtr<UVerticalBox> DialogueContent;

    UPROPERTY()
    TObjectPtr<UTextBlock> SpeakerText;

    UPROPERTY()
    TObjectPtr<UTextBlock> DialogueText;
};
