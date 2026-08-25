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

private:

    /*
     * ============================================================
     * CHARACTER CONSTRUCTION
     * ============================================================
     */

    void BuildCharacter();


    /*
     * ============================================================
     * CHARACTER ROOT
     * ============================================================
     */

    UPROPERTY()
    TObjectPtr<USceneComponent> CharacterRoot;


    /*
     * ============================================================
     * HEAD
     * ============================================================
     */

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Head;


    /*
     * ============================================================
     * TORSO
     * ============================================================
     */

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> Torso;


    /*
     * ============================================================
     * ARMS
     * ============================================================
     */

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> LeftArm;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> RightArm;


    /*
     * ============================================================
     * LEGS
     * ============================================================
     */

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> LeftLeg;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> RightLeg;


    /*
     * ============================================================
     * FEET
     * ============================================================
     */

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> LeftFoot;

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> RightFoot;
};