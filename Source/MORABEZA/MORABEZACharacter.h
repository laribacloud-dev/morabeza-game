#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MORABEZACharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMORABEZAInteractionComponent;

UCLASS()
class MORABEZA_API AMORABEZACharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMORABEZACharacter();

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Interact();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, Category = "Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMORABEZAInteractionComponent> InteractionComponent;
};
