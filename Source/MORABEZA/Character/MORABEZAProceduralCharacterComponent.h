#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MORABEZAProceduralCharacterComponent.generated.h"

class UStaticMeshComponent;

UCLASS(
    ClassGroup = (MORABEZA),
    meta = (BlueprintSpawnableComponent)
)
class MORABEZA_API UMORABEZAProceduralCharacterComponent
    : public USceneComponent
{
    GENERATED_BODY()

public:

    UMORABEZAProceduralCharacterComponent();

protected:

    virtual void BeginPlay() override;

    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction
    ) override;

private:

    void BuildCharacter();

    void UpdateAnimation(
        float DeltaTime
    );

    UPROPERTY()
    TObjectPtr<USceneComponent> CharacterRoot;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Head;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Hair;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Neck;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Torso;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Hips;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> LeftArm;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> RightArm;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> LeftLeg;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> RightLeg;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> LeftFoot;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> RightFoot;

    FRotator InitialLeftArmRotation;
    FRotator InitialRightArmRotation;

    FRotator InitialLeftLegRotation;
    FRotator InitialRightLegRotation;

    FVector InitialCharacterRootLocation;

    FVector InitialHeadLocation;

    float AnimationTime = 0.0f;

    float CurrentAnimationWeight = 0.0f;
};
