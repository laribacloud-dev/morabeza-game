#include "MORABEZAProceduralCharacterComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UMORABEZAProceduralCharacterComponent::UMORABEZAProceduralCharacterComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;

    /*
     * ============================================================
     * CHARACTER ROOT
     * ============================================================
     */

    CharacterRoot =
        CreateDefaultSubobject<USceneComponent>(
            TEXT("CharacterRoot")
        );

    CharacterRoot->SetupAttachment(this);

    /*
     * ============================================================
     * BODY PARTS
     * ============================================================
     */

    Head =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("Head")
        );
    Head->SetupAttachment(CharacterRoot);

    Hair =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("Hair")
        );
    Hair->SetupAttachment(CharacterRoot);

    Neck =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("Neck")
        );
    Neck->SetupAttachment(CharacterRoot);

    Torso =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("Torso")
        );
    Torso->SetupAttachment(CharacterRoot);

    Hips =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("Hips")
        );
    Hips->SetupAttachment(CharacterRoot);

    LeftArm =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("LeftArm")
        );
    LeftArm->SetupAttachment(CharacterRoot);

    RightArm =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("RightArm")
        );
    RightArm->SetupAttachment(CharacterRoot);

    LeftLeg =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("LeftLeg")
        );
    LeftLeg->SetupAttachment(CharacterRoot);

    RightLeg =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("RightLeg")
        );
    RightLeg->SetupAttachment(CharacterRoot);

    LeftFoot =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("LeftFoot")
        );
    LeftFoot->SetupAttachment(CharacterRoot);

    RightFoot =
        CreateDefaultSubobject<UStaticMeshComponent>(
            TEXT("RightFoot")
        );
    RightFoot->SetupAttachment(CharacterRoot);

    /*
     * ============================================================
     * ENGINE PRIMITIVES
     * ============================================================
     */

    UStaticMesh* CubeMesh =
        Cast<UStaticMesh>(
            StaticLoadObject(
                UStaticMesh::StaticClass(),
                nullptr,
                TEXT("/Engine/BasicShapes/Cube.Cube")
            )
        );

    UStaticMesh* SphereMesh =
        Cast<UStaticMesh>(
            StaticLoadObject(
                UStaticMesh::StaticClass(),
                nullptr,
                TEXT("/Engine/BasicShapes/Sphere.Sphere")
            )
        );

    UStaticMesh* CylinderMesh =
        Cast<UStaticMesh>(
            StaticLoadObject(
                UStaticMesh::StaticClass(),
                nullptr,
                TEXT("/Engine/BasicShapes/Cylinder.Cylinder")
            )
        );

    if (!CubeMesh || !SphereMesh || !CylinderMesh)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA PROCEDURAL CHARACTER ERROR: "
                "Required engine primitive mesh could not be loaded."
            )
        );

        return;
    }

    /*
     * ============================================================
     * MESH ASSIGNMENT
     * ============================================================
     */

    Head->SetStaticMesh(SphereMesh);
    Hair->SetStaticMesh(SphereMesh);

    Neck->SetStaticMesh(CylinderMesh);

    Torso->SetStaticMesh(CylinderMesh);
    Hips->SetStaticMesh(CylinderMesh);

    LeftArm->SetStaticMesh(CylinderMesh);
    RightArm->SetStaticMesh(CylinderMesh);

    LeftLeg->SetStaticMesh(CylinderMesh);
    RightLeg->SetStaticMesh(CylinderMesh);

    LeftFoot->SetStaticMesh(CubeMesh);
    RightFoot->SetStaticMesh(CubeMesh);

    /*
     * ============================================================
     * VISIBILITY
     * ============================================================
     */

    Head->SetVisibility(true);
    Hair->SetVisibility(true);
    Neck->SetVisibility(true);
    Torso->SetVisibility(true);
    Hips->SetVisibility(true);

    LeftArm->SetVisibility(true);
    RightArm->SetVisibility(true);

    LeftLeg->SetVisibility(true);
    RightLeg->SetVisibility(true);

    LeftFoot->SetVisibility(true);
    RightFoot->SetVisibility(true);

    Head->SetHiddenInGame(false);
    Hair->SetHiddenInGame(false);
    Neck->SetHiddenInGame(false);
    Torso->SetHiddenInGame(false);
    Hips->SetHiddenInGame(false);

    LeftArm->SetHiddenInGame(false);
    RightArm->SetHiddenInGame(false);

    LeftLeg->SetHiddenInGame(false);
    RightLeg->SetHiddenInGame(false);

    LeftFoot->SetHiddenInGame(false);
    RightFoot->SetHiddenInGame(false);

    /*
     * ============================================================
     * BLOCKOUT V3
     * ============================================================
     */

    Head->SetRelativeLocation(
        FVector(0.f, 0.f, 185.f)
    );

    Head->SetRelativeScale3D(
        FVector(0.34f, 0.32f, 0.40f)
    );

    Hair->SetRelativeLocation(
        FVector(-8.f, 0.f, 193.f)
    );

    Hair->SetRelativeScale3D(
        FVector(0.39f, 0.37f, 0.46f)
    );

    Neck->SetRelativeLocation(
        FVector(0.f, 0.f, 155.f)
    );

    Neck->SetRelativeScale3D(
        FVector(0.13f, 0.13f, 0.20f)
    );

    Torso->SetRelativeLocation(
        FVector(0.f, 0.f, 121.f)
    );

    Torso->SetRelativeScale3D(
        FVector(0.50f, 0.30f, 0.66f)
    );

    Hips->SetRelativeLocation(
        FVector(0.f, 0.f, 77.f)
    );

    Hips->SetRelativeScale3D(
        FVector(0.56f, 0.37f, 0.25f)
    );

    LeftArm->SetRelativeLocation(
        FVector(0.f, -48.f, 116.f)
    );

    LeftArm->SetRelativeScale3D(
        FVector(0.16f, 0.16f, 0.58f)
    );

    RightArm->SetRelativeLocation(
        FVector(0.f, 48.f, 116.f)
    );

    RightArm->SetRelativeScale3D(
        FVector(0.16f, 0.16f, 0.58f)
    );

    LeftLeg->SetRelativeLocation(
        FVector(0.f, -19.f, 35.f)
    );

    LeftLeg->SetRelativeScale3D(
        FVector(0.20f, 0.20f, 0.70f)
    );

    RightLeg->SetRelativeLocation(
        FVector(0.f, 19.f, 35.f)
    );

    RightLeg->SetRelativeScale3D(
        FVector(0.20f, 0.20f, 0.70f)
    );

    LeftFoot->SetRelativeLocation(
        FVector(22.f, -19.f, 8.f)
    );

    LeftFoot->SetRelativeScale3D(
        FVector(0.34f, 0.23f, 0.14f)
    );

    RightFoot->SetRelativeLocation(
        FVector(22.f, 19.f, 8.f)
    );

    RightFoot->SetRelativeScale3D(
        FVector(0.34f, 0.23f, 0.14f)
    );

    /*
     * ============================================================
     * DEBUG
     * ============================================================
     */

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA: Procedural female character "
            "BLOCKOUT V3 constructed successfully."
        )
    );
}


void UMORABEZAProceduralCharacterComponent::BeginPlay()
{
    Super::BeginPlay();

    /*
     * ============================================================
     * REGISTER PROCEDURAL HIERARCHY
     * ============================================================
     */

    if (CharacterRoot && !CharacterRoot->IsRegistered())
    {
        CharacterRoot->RegisterComponent();
    }

    if (Head && !Head->IsRegistered())
    {
        Head->RegisterComponent();
    }

    if (Hair && !Hair->IsRegistered())
    {
        Hair->RegisterComponent();
    }

    if (Neck && !Neck->IsRegistered())
    {
        Neck->RegisterComponent();
    }

    if (Torso && !Torso->IsRegistered())
    {
        Torso->RegisterComponent();
    }

    if (Hips && !Hips->IsRegistered())
    {
        Hips->RegisterComponent();
    }

    if (LeftArm && !LeftArm->IsRegistered())
    {
        LeftArm->RegisterComponent();
    }

    if (RightArm && !RightArm->IsRegistered())
    {
        RightArm->RegisterComponent();
    }

    if (LeftLeg && !LeftLeg->IsRegistered())
    {
        LeftLeg->RegisterComponent();
    }

    if (RightLeg && !RightLeg->IsRegistered())
    {
        RightLeg->RegisterComponent();
    }

    if (LeftFoot && !LeftFoot->IsRegistered())
    {
        LeftFoot->RegisterComponent();
    }

    if (RightFoot && !RightFoot->IsRegistered())
    {
        RightFoot->RegisterComponent();
    }

    /*
     * ============================================================
     * CAPTURE INITIAL TRANSFORMS
     * ============================================================
     *
     * Animation is always calculated from the original blockout
     * transforms. This prevents cumulative transform drift.
     */

    if (LeftArm)
    {
        InitialLeftArmRotation =
            LeftArm->GetRelativeRotation();
    }

    if (RightArm)
    {
        InitialRightArmRotation =
            RightArm->GetRelativeRotation();
    }

    if (LeftLeg)
    {
        InitialLeftLegRotation =
            LeftLeg->GetRelativeRotation();
    }

    if (RightLeg)
    {
        InitialRightLegRotation =
            RightLeg->GetRelativeRotation();
    }

    if (CharacterRoot)
    {
        InitialCharacterRootLocation =
            CharacterRoot->GetRelativeLocation();
    }

    if (Head)
    {
        InitialHeadLocation =
            Head->GetRelativeLocation();
    }

    /*
     * ============================================================
     * RESET ANIMATION STATE
     * ============================================================
     */

    AnimationTime = 0.0f;
    CurrentAnimationWeight = 0.0f;

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA: Procedural character ACTIVE. "
            "Animation system initialized."
        )
    );
}


void UMORABEZAProceduralCharacterComponent::BuildCharacter()
{
    /*
     * Character construction is currently performed
     * in the component constructor.
     *
     * This function intentionally remains available for
     * future procedural-generation expansion.
     */
}


/*
 * ================================================================
 * PROCEDURAL ANIMATION SYSTEM
 * ================================================================
 *
 * Temporary animation system for MORABEZA V3.
 *
 * Animation states:
 *
 *     IDLE
 *       |
 *       v
 *     WALK
 *       |
 *       v
 *     SPRINT
 *
 * The final artist-created skeletal character will eventually
 * replace this system.
 *
 * ================================================================
 */

void UMORABEZAProceduralCharacterComponent::TickComponent(
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

    UpdateAnimation(DeltaTime);
}


void UMORABEZAProceduralCharacterComponent::UpdateAnimation(
    float DeltaTime
)
{
    AActor* Owner = GetOwner();

    if (!Owner)
    {
        return;
    }

    /*
     * ============================================================
     * GET MOVEMENT SPEED
     * ============================================================
     */

    FVector Velocity =
        Owner->GetVelocity();

    Velocity.Z = 0.0f;

    float Speed =
        Velocity.Size();

    /*
     * Prefer CharacterMovementComponent velocity when available.
     */

    ACharacter* Character =
        Cast<ACharacter>(Owner);

    UCharacterMovementComponent* MovementComponent =
        nullptr;

    if (Character)
    {
        MovementComponent =
            Character->GetCharacterMovement();

        if (MovementComponent)
        {
            FVector MovementVelocity =
                MovementComponent->Velocity;

            MovementVelocity.Z = 0.0f;

            Speed =
                MovementVelocity.Size();
        }
    }

    /*
     * ============================================================
     * MOVEMENT PARAMETERS
     * ============================================================
     */

    const float WalkSpeed = 250.0f;
    const float SprintSpeed = 600.0f;

    const float MovementAlpha =
        FMath::Clamp(
            Speed / SprintSpeed,
            0.0f,
            1.0f
        );

    /*
     * ============================================================
     * LOCOMOTION WEIGHT
     * ============================================================
     *
     * 0 = idle
     * 1 = full locomotion
     */

    const float TargetWeight =
        FMath::Clamp(
            Speed / WalkSpeed,
            0.0f,
            1.0f
        );

    CurrentAnimationWeight =
        FMath::FInterpTo(
            CurrentAnimationWeight,
            TargetWeight,
            DeltaTime,
            9.0f
        );

    /*
     * ============================================================
     * LOCOMOTION CYCLE SPEED
     * ============================================================
     */

    const float LocomotionSpeed =
        FMath::Lerp(
            4.5f,
            9.0f,
            MovementAlpha
        );

    if (CurrentAnimationWeight > 0.01f)
    {
        AnimationTime +=
            DeltaTime *
            LocomotionSpeed;
    }

    /*
     * ============================================================
     * IDLE MOTION
     * ============================================================
     */

    const float WorldTime =
        GetWorld()
            ? GetWorld()->GetTimeSeconds()
            : 0.0f;

    const float IdleWave =
        FMath::Sin(
            WorldTime * 1.8f
        );

    const float IdleWaveSlow =
        FMath::Sin(
            WorldTime * 0.9f
        );

    /*
     * ============================================================
     * LOCOMOTION WAVES
     * ============================================================
     */

    const float WalkWave =
        FMath::Sin(
            AnimationTime
        );

    const float OppositeWave =
        FMath::Sin(
            AnimationTime + PI
        );

    /*
     * ============================================================
     * ARM SWING
     * ============================================================
     */

    const float ArmSwing =
        FMath::Lerp(
            24.0f,
            34.0f,
            MovementAlpha
        );

    const float ArmRoll =
        FMath::Lerp(
            3.0f,
            6.0f,
            MovementAlpha
        );

    if (LeftArm)
    {
        FRotator Rotation =
            InitialLeftArmRotation;

        Rotation.Pitch +=
            OppositeWave *
            ArmSwing *
            CurrentAnimationWeight;

        Rotation.Roll +=
            WalkWave *
            ArmRoll *
            CurrentAnimationWeight;

        Rotation.Yaw +=
            IdleWave *
            1.5f *
            (1.0f - CurrentAnimationWeight);

        LeftArm->SetRelativeRotation(
            Rotation
        );
    }

    if (RightArm)
    {
        FRotator Rotation =
            InitialRightArmRotation;

        Rotation.Pitch +=
            WalkWave *
            ArmSwing *
            CurrentAnimationWeight;

        Rotation.Roll +=
            OppositeWave *
            ArmRoll *
            CurrentAnimationWeight;

        Rotation.Yaw +=
            IdleWave *
            -1.5f *
            (1.0f - CurrentAnimationWeight);

        RightArm->SetRelativeRotation(
            Rotation
        );
    }

    /*
     * ============================================================
     * LEG SWING
     * ============================================================
     */

    const float LegSwing =
        FMath::Lerp(
            25.0f,
            38.0f,
            MovementAlpha
        );

    if (LeftLeg)
    {
        FRotator Rotation =
            InitialLeftLegRotation;

        Rotation.Pitch +=
            WalkWave *
            LegSwing *
            CurrentAnimationWeight;

        Rotation.Roll +=
            OppositeWave *
            1.5f *
            CurrentAnimationWeight;

        LeftLeg->SetRelativeRotation(
            Rotation
        );
    }

    if (RightLeg)
    {
        FRotator Rotation =
            InitialRightLegRotation;

        Rotation.Pitch +=
            OppositeWave *
            LegSwing *
            CurrentAnimationWeight;

        Rotation.Roll +=
            WalkWave *
            1.5f *
            CurrentAnimationWeight;

        RightLeg->SetRelativeRotation(
            Rotation
        );
    }

    /*
     * ============================================================
     * BODY BOB
     * ============================================================
     */

    if (CharacterRoot)
    {
        FVector Location =
            InitialCharacterRootLocation;

        const float WalkBob =
            FMath::Abs(
                FMath::Sin(
                    AnimationTime * 2.0f
                )
            ) *
            FMath::Lerp(
                2.0f,
                5.5f,
                MovementAlpha
            ) *
            CurrentAnimationWeight;

        const float IdleBob =
            IdleWaveSlow *
            1.2f *
            (1.0f - CurrentAnimationWeight);

        Location.Z +=
            WalkBob +
            IdleBob;

        CharacterRoot->SetRelativeLocation(
            Location
        );
    }

    /*
     * ============================================================
     * HIP SWAY
     * ============================================================
     */

    if (Hips)
    {
        FRotator HipRotation =
            FRotator::ZeroRotator;

        HipRotation.Yaw +=
            WalkWave *
            4.0f *
            CurrentAnimationWeight;

        HipRotation.Roll +=
            OppositeWave *
            2.5f *
            CurrentAnimationWeight;

        Hips->SetRelativeRotation(
            HipRotation
        );
    }

    /*
     * ============================================================
     * TORSO COUNTER ROTATION
     * ============================================================
     */

    if (Torso)
    {
        FRotator TorsoRotation =
            FRotator::ZeroRotator;

        TorsoRotation.Yaw +=
            OppositeWave *
            2.5f *
            CurrentAnimationWeight;

        TorsoRotation.Roll +=
            WalkWave *
            1.5f *
            CurrentAnimationWeight;

        Torso->SetRelativeRotation(
            TorsoRotation
        );
    }

    /*
     * ============================================================
     * HEAD STABILIZATION
     * ============================================================
     */

    if (Head)
    {
        FVector HeadLocation =
            InitialHeadLocation;

        const float WalkingHeadBob =
            FMath::Sin(
                AnimationTime * 2.0f
            ) *
            1.0f *
            CurrentAnimationWeight;

        const float IdleHeadBob =
            IdleWaveSlow *
            0.7f *
            (1.0f - CurrentAnimationWeight);

        HeadLocation.Z +=
            WalkingHeadBob +
            IdleHeadBob;

        Head->SetRelativeLocation(
            HeadLocation
        );
    }

    /*
     * ============================================================
     * HAIR FOLLOW-THROUGH
     * ============================================================
     */

    if (Hair)
    {
        FRotator HairRotation =
            FRotator::ZeroRotator;

        HairRotation.Roll +=
            WalkWave *
            1.5f *
            CurrentAnimationWeight;

        HairRotation.Yaw +=
            OppositeWave *
            1.0f *
            CurrentAnimationWeight;

        Hair->SetRelativeRotation(
            HairRotation
        );
    }

    /*
     * ============================================================
     * FOOT ARTICULATION
     * ============================================================
     */

    if (LeftFoot)
    {
        FRotator FootRotation =
            FRotator::ZeroRotator;

        FootRotation.Pitch +=
            OppositeWave *
            10.0f *
            CurrentAnimationWeight;

        LeftFoot->SetRelativeRotation(
            FootRotation
        );
    }

    if (RightFoot)
    {
        FRotator FootRotation =
            FRotator::ZeroRotator;

        FootRotation.Pitch +=
            WalkWave *
            10.0f *
            CurrentAnimationWeight;

        RightFoot->SetRelativeRotation(
            FootRotation
        );
    }
}