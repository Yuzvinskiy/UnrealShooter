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

    void StartFire();
    void StopFire();
    bool IsFiring() const;
    void NextWeapon();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentAmmoData(FAmmoData& CurrentAmmo) const;
   

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<AUSBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    


private:
    UPROPERTY()
    AUSBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AUSBaseWeapon*> Weapons;

    bool EquipAnimInProgress = false;
    int32 CurrentWeaponIndex = 0;

    void SpawnWeapons();
    void AttachWeaponToSocket(AUSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponIndex);

    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    bool CanFire() const;
    bool CanEquip() const;
};
