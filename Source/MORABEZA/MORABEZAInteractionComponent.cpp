#include "MORABEZAInteractionComponent.h"

#include "MORABEZAInteractable.h"

#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UMORABEZAInteractionComponent::UMORABEZAInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    InteractionDistance = 350.0f;
    InteractionTraceDistance = 500.0f;
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

void UMORABEZAInteractionComponent::SetInteractionTarget(
    AActor* NewTarget
)
{
    AActor* PreviousTarget = CurrentTarget.Get();

    if (PreviousTarget == NewTarget)
    {
        return;
    }

    CurrentTarget = NewTarget;

    if (NewTarget)
    {
        const FText Prompt =
            IMORABEZAInteractable::Execute_GetInteractionPrompt(
                NewTarget
            );

        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA INTERACTION: TARGET ACQUIRED - %s"
            ),
            *NewTarget->GetName()
        );

        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA INTERACTION: Prompt = %s"
            ),
            *Prompt.ToString()
        );

        OnPromptChanged.Broadcast(Prompt);

        return;
    }

    if (PreviousTarget)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT(
                "MORABEZA INTERACTION: TARGET LOST - %s"
            ),
            *PreviousTarget->GetName()
        );
    }

    OnPromptChanged.Broadcast(
        FText::GetEmpty()
    );
}

void UMORABEZAInteractionComponent::UpdateInteractionTarget()
{
    ACharacter* Character =
        Cast<ACharacter>(GetOwner());

    if (!Character)
    {
        SetInteractionTarget(nullptr);
        return;
    }

    UWorld* World = GetWorld();

    if (!World)
    {
        SetInteractionTarget(nullptr);
        return;
    }

    /*
     * ============================================================
     * MORABEZA ALBION-STYLE INTERACTION
     * ============================================================
     *
     * The gameplay camera is intentionally positioned high and
     * angled downward.
     *
     * Therefore interaction does NOT use the camera center ray.
     *
     * Interaction follows the character's horizontal forward
     * direction instead.
     *
     * This makes interaction independent from the camera pitch.
     */

    const FVector CharacterLocation =
        Character->GetActorLocation();

    FVector Forward =
        Character->GetActorForwardVector();

    /*
     * Keep interaction horizontal.
     */

    Forward.Z = 0.0f;

    if (!Forward.Normalize())
    {
        SetInteractionTarget(nullptr);
        return;
    }

    /*
     * Start the sweep slightly above the character's origin.
     */

    const FVector TraceStart =
        CharacterLocation +
        FVector(0.0f, 0.0f, 60.0f);

    const FVector TraceEnd =
        TraceStart +
        (
            Forward *
            InteractionTraceDistance
        );

    FHitResult HitResult;

    FCollisionQueryParams QueryParams(
        SCENE_QUERY_STAT(MORABEZAInteractionTrace),
        true,
        Character
    );

    QueryParams.bTraceComplex = true;

    /*
     * Sphere sweep gives the player a forgiving interaction area
     * instead of requiring pixel-perfect alignment.
     */

    const float SweepRadius = 65.0f;

    const bool bHit =
        World->SweepSingleByChannel(
            HitResult,
            TraceStart,
            TraceEnd,
            FQuat::Identity,
            ECC_Visibility,
            FCollisionShape::MakeSphere(SweepRadius),
            QueryParams
        );

    /*
     * Temporary debug line.
     *
     * Green = something was hit.
     * Red   = nothing was hit.
     */

    DrawDebugLine(
        World,
        TraceStart,
        TraceEnd,
        bHit
            ? FColor::Green
            : FColor::Red,
        false,
        0.05f,
        0,
        2.0f
    );

    if (!bHit)
    {
        SetInteractionTarget(nullptr);
        return;
    }

    AActor* HitActor =
        HitResult.GetActor();

    if (!HitActor)
    {
        SetInteractionTarget(nullptr);
        return;
    }

    /*
     * ============================================================
     * INTERACTABLE CHECK
     * ============================================================
     */

    if (
        !HitActor->GetClass()->ImplementsInterface(
            UMORABEZAInteractable::StaticClass()
        )
    )
    {
        SetInteractionTarget(nullptr);
        return;
    }

    /*
     * ============================================================
     * PLAYER DISTANCE CHECK
     * ============================================================
     */

    const float DistanceSquared =
        FVector::DistSquared(
            CharacterLocation,
            HitActor->GetActorLocation()
        );

    const float MaxDistanceSquared =
        FMath::Square(InteractionDistance);

    if (DistanceSquared > MaxDistanceSquared)
    {
        SetInteractionTarget(nullptr);
        return;
    }

    SetInteractionTarget(HitActor);
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

    /*
     * Refresh the target immediately before interaction.
     */

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