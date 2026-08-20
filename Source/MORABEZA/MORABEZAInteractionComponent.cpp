#include "MORABEZAInteractionComponent.h"

#include "MORABEZAInteractable.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Engine/OverlapResult.h"

UMORABEZAInteractionComponent::UMORABEZAInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    InteractionDistance = 350.0f;
}

void UMORABEZAInteractionComponent::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA INTERACTION: Component started.")
    );

    UpdateInteractionTarget();
}

void UMORABEZAInteractionComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction
)
{
    Super::TickComponent(
        DeltaTime,
        TickType,
        ThisTickFunction
    );

    UpdateInteractionTarget();
}

void UMORABEZAInteractionComponent::UpdateInteractionTarget()
{
    ACharacter* Character =
        Cast<ACharacter>(GetOwner());

    if (!Character)
    {
        CurrentTarget.Reset();
        OnPromptChanged.Broadcast(FText::GetEmpty());
        return;
    }

    UWorld* World = GetWorld();

    if (!World)
    {
        CurrentTarget.Reset();
        OnPromptChanged.Broadcast(FText::GetEmpty());
        return;
    }

    const FVector Center =
        Character->GetActorLocation();

    TArray<FOverlapResult> Overlaps;

    FCollisionQueryParams QueryParams(
        SCENE_QUERY_STAT(MORABEZAInteraction),
        false,
        Character
    );

    /*
     * ============================================================
     * INTERACTION COLLISION
     * ============================================================
     *
     * Contacts use WorldStatic collision by default.
     *
     * We therefore search BOTH WorldStatic and WorldDynamic.
     *
     * This fixes the previous situation where a contact could be
     * physically inside the interaction sphere but invisible to
     * the interaction query.
     */

    FCollisionObjectQueryParams ObjectQueryParams;

    ObjectQueryParams.AddObjectTypesToQuery(
        ECC_WorldStatic
    );

    ObjectQueryParams.AddObjectTypesToQuery(
        ECC_WorldDynamic
    );

    const bool bFoundObjects =
        World->OverlapMultiByObjectType(
            Overlaps,
            Center,
            FQuat::Identity,
            ObjectQueryParams,
            FCollisionShape::MakeSphere(
                InteractionDistance
            ),
            QueryParams
        );

    AActor* BestTarget = nullptr;

    float BestDistanceSquared =
        TNumericLimits<float>::Max();

    if (bFoundObjects)
    {
        for (const FOverlapResult& Result : Overlaps)
        {
            AActor* Actor =
                Result.GetActor();

            if (!Actor || Actor == Character)
            {
                continue;
            }

            if (
                !Actor->GetClass()->ImplementsInterface(
                    UMORABEZAInteractable::StaticClass()
                )
            )
            {
                continue;
            }

            const float DistanceSquared =
                FVector::DistSquared(
                    Center,
                    Actor->GetActorLocation()
                );

            if (
                DistanceSquared <
                BestDistanceSquared
            )
            {
                BestDistanceSquared =
                    DistanceSquared;

                BestTarget =
                    Actor;
            }
        }
    }

    if (BestTarget)
    {
        CurrentTarget =
            BestTarget;

        const FText Prompt =
            IMORABEZAInteractable::Execute_GetInteractionPrompt(
                BestTarget
            );

        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA INTERACTION: TARGET FOUND - %s at %.1f units"
            ),
            *BestTarget->GetName(),
            FMath::Sqrt(BestDistanceSquared)
        );

        OnPromptChanged.Broadcast(Prompt);

        return;
    }

    if (CurrentTarget.IsValid())
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA INTERACTION: TARGET LOST."
            )
        );
    }

    CurrentTarget.Reset();

    OnPromptChanged.Broadcast(
        FText::GetEmpty()
    );
}

void UMORABEZAInteractionComponent::TryInteract()
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA INTERACTION: E pressed - TryInteract called."
        )
    );

    UpdateInteractionTarget();

    AActor* Target =
        CurrentTarget.Get();

    if (
        Target &&
        Target->GetClass()->ImplementsInterface(
            UMORABEZAInteractable::StaticClass()
        )
    )
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA INTERACTION: Executing interaction on %s."
            ),
            *Target->GetName()
        );

        IMORABEZAInteractable::Execute_Interact(
            Target,
            GetOwner()
        );

        return;
    }

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA INTERACTION: No valid target."
        )
    );
}
