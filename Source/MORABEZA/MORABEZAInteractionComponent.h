#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MORABEZAInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMORABEZAInteractionPromptChanged, const FText&, Prompt);

UCLASS(ClassGroup=(MORABEZA), BlueprintType, meta=(BlueprintSpawnableComponent))
class MORABEZA_API UMORABEZAInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMORABEZAInteractionComponent();

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void TryInteract();

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void UpdateInteractionTarget();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionDistance = 250.0f;

    UPROPERTY(BlueprintAssignable, Category = "Interaction")
    FMORABEZAInteractionPromptChanged OnPromptChanged;

protected:
    virtual void BeginPlay() override;

private:
    TWeakObjectPtr<AActor> CurrentTarget;
};
