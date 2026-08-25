#include "MORABEZAProceduralCharacterComponent.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

UMORABEZAProceduralCharacterComponent::UMORABEZAProceduralCharacterComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    CharacterRoot = CreateDefaultSubobject<USceneComponent>(
        TEXT("CharacterRoot")
    );
    CharacterRoot->SetupAttachment(this);

    Head = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("Head")
    );
    Head->SetupAttachment(CharacterRoot);

    Torso = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("Torso")
    );
    Torso->SetupAttachment(CharacterRoot);

    LeftArm = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("LeftArm")
    );
    LeftArm->SetupAttachment(CharacterRoot);

    RightArm = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("RightArm")
    );
    RightArm->SetupAttachment(CharacterRoot);

    LeftLeg = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("LeftLeg")
    );
    LeftLeg->SetupAttachment(CharacterRoot);

    RightLeg = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("RightLeg")
    );
    RightLeg->SetupAttachment(CharacterRoot);

    LeftFoot = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("LeftFoot")
    );
    LeftFoot->SetupAttachment(CharacterRoot);

    RightFoot = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("RightFoot")
    );
    RightFoot->SetupAttachment(CharacterRoot);
}


void UMORABEZAProceduralCharacterComponent::BeginPlay()
{
    Super::BeginPlay();

    BuildCharacter();
}


void UMORABEZAProceduralCharacterComponent::BuildCharacter()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
        TEXT("/Engine/BasicShapes/Cube.Cube")
    );

    if (!CubeMesh.Succeeded())
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("MORABEZA: Failed to load Cube mesh.")
        );

        return;
    }

    UStaticMesh* Mesh = CubeMesh.Object;

    Head->SetStaticMesh(Mesh);
    Torso->SetStaticMesh(Mesh);
    LeftArm->SetStaticMesh(Mesh);
    RightArm->SetStaticMesh(Mesh);
    LeftLeg->SetStaticMesh(Mesh);
    RightLeg->SetStaticMesh(Mesh);
    LeftFoot->SetStaticMesh(Mesh);
    RightFoot->SetStaticMesh(Mesh);


    // Head
    Head->SetRelativeLocation(
        FVector(0.f, 0.f, 180.f)
    );

    Head->SetRelativeScale3D(
        FVector(0.45f, 0.45f, 0.45f)
    );


    // Torso
    Torso->SetRelativeLocation(
        FVector(0.f, 0.f, 125.f)
    );

    Torso->SetRelativeScale3D(
        FVector(0.65f, 0.38f, 0.85f)
    );


    // Left arm
    LeftArm->SetRelativeLocation(
        FVector(0.f, -55.f, 125.f)
    );

    LeftArm->SetRelativeScale3D(
        FVector(0.28f, 0.28f, 0.75f)
    );


    // Right arm
    RightArm->SetRelativeLocation(
        FVector(0.f, 55.f, 125.f)
    );

    RightArm->SetRelativeScale3D(
        FVector(0.28f, 0.28f, 0.75f)
    );


    // Left leg
    LeftLeg->SetRelativeLocation(
        FVector(0.f, -25.f, 55.f)
    );

    LeftLeg->SetRelativeScale3D(
        FVector(0.30f, 0.30f, 0.85f)
    );


    // Right leg
    RightLeg->SetRelativeLocation(
        FVector(0.f, 25.f, 55.f)
    );

    RightLeg->SetRelativeScale3D(
        FVector(0.30f, 0.30f, 0.85f)
    );


    // Left foot
    LeftFoot->SetRelativeLocation(
        FVector(35.f, -25.f, 15.f)
    );

    LeftFoot->SetRelativeScale3D(
        FVector(0.45f, 0.32f, 0.22f)
    );


    // Right foot
    RightFoot->SetRelativeLocation(
        FVector(35.f, 25.f, 15.f)
    );

    RightFoot->SetRelativeScale3D(
        FVector(0.45f, 0.32f, 0.22f)
    );


    UE_LOG(
        LogTemp,
        Log,
        TEXT("MORABEZA: Procedural character built.")
    );
}