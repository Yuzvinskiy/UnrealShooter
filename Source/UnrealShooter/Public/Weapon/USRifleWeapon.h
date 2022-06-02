// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Weapon/USBaseWeapon.h"
#include "USRifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class UNREALSHOOTER_API AUSRifleWeapon : public AUSBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 30.0f;

    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;

    void MakeDamage(const FHitResult& HitResult);
};
