// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "USBaseCharacter.generated.h"

class UUSHealthComponent;
class UUSWeaponComponent;
class USoundCue;

UCLASS()
class UNREALSHOOTER_API AUSBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AUSBaseCharacter(const FObjectInitializer& ObjInit);

protected:

    virtual void OnHealthChanged(float Health, float HealthDelta);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UUSHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UUSWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    UPROPERTY(EditDefaultsOnly, Category = "TeamSettings")
    FName MaterialColorName = "MeatllicCCTint";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* DeathSound;

    virtual void OnDeath();
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor& Color);

private:
    

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
