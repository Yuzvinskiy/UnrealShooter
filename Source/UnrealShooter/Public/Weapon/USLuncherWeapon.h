// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Weapon/USBaseWeapon.h"
#include "USLuncherWeapon.generated.h"

class AUSProjectile;
class USoundCue;

UCLASS()
class UNREALSHOOTER_API AUSLuncherWeapon : public AUSBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon");
    TSubclassOf<AUSProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound;

    virtual void MakeShot() override;
};
