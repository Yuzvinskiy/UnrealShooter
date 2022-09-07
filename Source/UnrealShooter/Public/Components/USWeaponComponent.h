// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USCoreTypes.h"
#include "USWeaponComponent.generated.h"

class AUSBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALSHOOTER_API UUSWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UUSWeaponComponent();

    virtual void StartFire();
    void StopFire();
    bool IsFiring() const;
    virtual void NextWeapon();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentAmmoData(FAmmoData& CurrentAmmo) const;

    bool TryToAddAmmo(TSubclassOf<AUSBaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<AUSBaseWeapon> WeaponType);

    void Zoom(bool Enabled);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<AUSBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    AUSBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AUSBaseWeapon*> Weapons;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;
    int32 CurrentWeaponIndex = 0;

    void EquipWeapon(int32 WeaponIndex);

private:
    bool EquipAnimInProgress = false;
   

    void SpawnWeapons();
    void AttachWeaponToSocket(AUSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
};
