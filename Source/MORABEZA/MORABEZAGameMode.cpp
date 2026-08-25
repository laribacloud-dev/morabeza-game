#include "MORABEZAGameMode.h"

#include "MORABEZACharacter.h"
#include "MORABEZAHUD.h"
#include "MORABEZAContactActor.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

AMORABEZAGameMode::AMORABEZAGameMode()
{
    DefaultPawnClass = AMORABEZACharacter::StaticClass();

    HUDClass = AMORABEZAHUD::StaticClass();
}

void AMORABEZAGameMode::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("MORABEZA GAMEMODE: BeginPlay.")
    );

    SpawnTestContact();
}

void AMORABEZAGameMode::SpawnTestContact()
{
    UWorld* World = GetWorld();

    if (!World)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("MORABEZA GAMEMODE: World is NULL.")
        );

        return;
    }

    APlayerController* PlayerController =
        World->GetFirstPlayerController();

    if (!PlayerController)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("MORABEZA GAMEMODE: PlayerController is NULL.")
        );

        return;
    }

    APawn* PlayerPawn =
        PlayerController->GetPawn();

    if (!PlayerPawn)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("MORABEZA GAMEMODE: PlayerPawn is NULL.")
        );

        return;
    }

    FVector CameraLocation;
    FRotator CameraRotation;

    PlayerController->GetPlayerViewPoint(
        CameraLocation,
        CameraRotation
    );

    /*
     * Spawn the test contact in the direction the
     * player is actually looking.
     */
    FVector ViewDirection =
        CameraRotation.Vector();

    /*
     * Project the camera direction onto the horizontal
     * plane so the test contact stays near ground level.
     */
    ViewDirection.Z = 0.0f;

    if (ViewDirection.IsNearlyZero())
    {
        ViewDirection =
            PlayerPawn->GetActorForwardVector();
    }

    ViewDirection.Normalize();

    const FVector SpawnLocation =
        PlayerPawn->GetActorLocation() +
        ViewDirection * 250.0f;

    FActorSpawnParameters SpawnParams;

    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AMORABEZAContactActor* Contact =
        World->SpawnActor<AMORABEZAContactActor>(
            AMORABEZAContactActor::StaticClass(),
            SpawnLocation,
            FRotator::ZeroRotator,
            SpawnParams
        );

    if (!Contact)
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT(
                "MORABEZA GAMEMODE: Failed to spawn test contact."
            )
        );

        return;
    }

    Contact->ContactName =
        FText::FromString(TEXT("Test Contact"));

    Contact->MissionId =
        TEXT("TEST_INTERACTION");

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA GAMEMODE: TEST CONTACT SPAWNED."
        )
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA GAMEMODE: Camera Location=%s"
        ),
        *CameraLocation.ToString()
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA GAMEMODE: Camera Rotation=%s"
        ),
        *CameraRotation.ToString()
    );

    UE_LOG(
        LogTemp,
        Warning,
        TEXT(
            "MORABEZA GAMEMODE: Test Contact Location=%s"
        ),
        *Contact->GetActorLocation().ToString()
    );
}
