#include "MORABEZAContactActor.h"

#include "Components/StaticMeshComponent.h"

#include "Dialogue/MORABEZADialogueComponent.h"

#include "GameFramework/PlayerController.h"

#include "MORABEZAHUD.h"

#include "UObject/ConstructorHelpers.h"

AMORABEZAContactActor::AMORABEZAContactActor()
{
    PrimaryActorTick.bCanEverTick = false;

    /*
     * ============================================================
     * CONTACT MESH
     * ============================================================
     */

    Mesh =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("Mesh")
        );

    RootComponent = Mesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        MeshAsset(
            TEXT("/Engine/BasicShapes/Cube.Cube")
        );

    if (MeshAsset.Succeeded())
    {
        Mesh->SetStaticMesh(
            MeshAsset.Object
        );
    }

    Mesh->SetCollisionEnabled(
        ECollisionEnabled::QueryAndPhysics
    );

    Mesh->SetCollisionObjectType(
        ECC_WorldDynamic
    );

    Mesh->SetCollisionResponseToAllChannels(
        ECR_Block
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA CONTACT: Collision configured as WorldDynamic."
        )
    );

    /*
     * ============================================================
     * DIALOGUE COMPONENT
     * ============================================================
     */

    DialogueComponent =
        CreateDefaultSubobject<UMORABEZADialogueComponent>(
            TEXT("DialogueComponent")
        );
}

void AMORABEZAContactActor::Interact_Implementation(
    AActor* Interactor
)
{
    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA CONTACT: %s interacted / Mission: %s"
        ),
        *ContactName.ToString(),
        *MissionId.ToString()
    );

    if (!DialogueComponent)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA CONTACT: DialogueComponent is NULL."
            )
        );

        return;
    }

    APlayerController* PlayerController =
        Cast<APlayerController>(
            Interactor
                ? Interactor->GetInstigatorController()
                : nullptr
        );

    if (!PlayerController)
    {
        PlayerController =
            Cast<APlayerController>(
                GetWorld()
                    ? GetWorld()->GetFirstPlayerController()
                    : nullptr
            );
    }

    if (!PlayerController)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA CONTACT: PlayerController unavailable."
            )
        );

        return;
    }

    AMORABEZAHUD* HUD =
        Cast<AMORABEZAHUD>(
            PlayerController->GetHUD()
        );

    if (!HUD)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA CONTACT: MORABEZAHUD unavailable."
            )
        );

        return;
    }

    /*
     * ============================================================
     * CONNECT DIALOGUE TO HUD
     * ============================================================
     *
     * The HUD owns the single authoritative dialogue UI.
     */

    DialogueComponent->OnDialogueLineChanged.RemoveAll(HUD);
    DialogueComponent->OnDialogueFinished.RemoveAll(HUD);

    DialogueComponent->OnDialogueLineChanged.AddDynamic(
        HUD,
        &AMORABEZAHUD::HandleDialogueLineChanged
    );

    DialogueComponent->OnDialogueFinished.AddDynamic(
        HUD,
        &AMORABEZAHUD::HandleDialogueFinished
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA CONTACT: Dialogue connected to HUD."
        )
    );

    /*
     * ============================================================
     * SET ACTIVE DIALOGUE COMPONENT
     * ============================================================
     *
     * The HUD needs to know which dialogue component should
     * receive subsequent E-key advance commands.
     */

    HUD->SetActiveDialogueComponent(
        DialogueComponent
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA CONTACT: Active dialogue component assigned to HUD."
        )
    );

    /*
     * ============================================================
     * START DIALOGUE
     * ============================================================
     */

    DialogueComponent->StartDialogue();
}

FText AMORABEZAContactActor::GetInteractionPrompt_Implementation()
    const
{
    return FText::Format(
        FText::FromString(
            TEXT("[E] Falar com {0}")
        ),
        ContactName
    );
}
