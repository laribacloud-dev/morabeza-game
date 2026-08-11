#include "MORABEZAContactActor.h"

#include "Engine/Engine.h"

AMORABEZAContactActor::AMORABEZAContactActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMORABEZAContactActor::Interact_Implementation(AActor* Interactor)
{
    UE_LOG(LogTemp, Log, TEXT("MORABEZA mission contact interacted: %s / Mission: %s"), *ContactName.ToString(), *MissionId.ToString());
}

FText AMORABEZAContactActor::GetInteractionPrompt_Implementation() const
{
    return FText::Format(FText::FromString(TEXT("Falar com {0}")), ContactName);
}
