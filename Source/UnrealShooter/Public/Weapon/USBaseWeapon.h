
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USCoreTypes.h"
#include "USBaseWeapon.generated.h"

class USkeletalMeshComponent;



UCLASS()
class UNREALSHOOTER_API AUSBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    AUSBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();
    bool IsFiring() const;

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetCurrentAmmoData() const {return CurrentAmmo; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10 , false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY()
    bool FireInProgress = false;

    virtual void BeginPlay() override;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

    void DecreaseAmmo();
    bool IsAmmoEmpty()const;
    bool IsClipEmpty()const;
    void ChangeClip();
    void LogAmmo();
    

   
    private:
    FAmmoData CurrentAmmo;
};
