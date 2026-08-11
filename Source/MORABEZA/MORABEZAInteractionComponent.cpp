#include "MORABEZAInteractionComponent.h"

#include "MORABEZAInteractable.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

UMORABEZAInteractionComponent::UMORABEZAInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMORABEZAInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
    UpdateInteractionTarget();
}

void UMORABEZAInteractionComponent::UpdateInteractionTarget()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
    {
        CurrentTarget.Reset();
        OnPromptChanged.Broadcast(FText::GetEmpty());
        return;
    }

    APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
    if (!PlayerController)
    {
        CurrentTarget.Reset();
        OnPromptChanged.Broadcast(FText::GetEmpty());
        return;
    }

    FVector CameraLocation;
    FRotator CameraRotation;
    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

    const FVector TraceEnd = CameraLocation + CameraRotation.Vector() * InteractionDistance;
    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(MORABEZAInteraction), true, Character);

    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        CameraLocation,
        TraceEnd,
        ECC_Visibility,
        Params);

    AActor* HitActor = bHit ? Hit.GetActor() : nullptr;
    if (HitActor && HitActor->GetClass()->ImplementsInterface(UMORABEZAInteractable::StaticClass()))
    {
        CurrentTarget = HitActor;
        OnPromptChanged.Broadcast(IMORABEZAInteractable::Execute_GetInteractionPrompt(HitActor));
        return;
    }

    CurrentTarget.Reset();
    OnPromptChanged.Broadcast(FText::GetEmpty());
}

void UMORABEZAInteractionComponent::TryInteract()
{
    UpdateInteractionTarget();

    AActor* Target = CurrentTarget.Get();
    if (Target && Target->GetClass()->ImplementsInterface(UMORABEZAInteractable::StaticClass()))
    {
        IMORABEZAInteractable::Execute_Interact(Target, GetOwner());
    }
}
