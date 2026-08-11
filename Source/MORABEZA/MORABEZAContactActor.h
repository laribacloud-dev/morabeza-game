#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MORABEZAInteractable.h"
#include "MORABEZAContactActor.generated.h"

UCLASS(Blueprintable)
class MORABEZA_API AMORABEZAContactActor : public AActor, public IMORABEZAInteractable
{
    GENERATED_BODY()

public:
    AMORABEZAContactActor();

    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual FText GetInteractionPrompt_Implementation() const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
    FName MissionId = TEXT("VOLTA_INTRO");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
    FText ContactName = FText::FromString(TEXT("Contact"));
};
