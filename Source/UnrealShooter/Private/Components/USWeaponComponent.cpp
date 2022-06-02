// UnrealShooter

#include "Components/USWeaponComponent.h"
#include "Weapon/USBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/USEquipFinished.h"

UUSWeaponComponent::UUSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    InitAnimations();
    CurrentWeaponIndex = 0;
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UUSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void UUSWeaponComponent::SpawnWeapons()
{

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<AUSBaseWeapon>(WeaponClass);
        if (!Weapon) continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void UUSWeaponComponent::AttachWeaponToSocket(AUSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UUSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    CurrentWeapon = Weapons[WeaponIndex];

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UUSWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}
void UUSWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void UUSWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UUSWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    Character->PlayAnimMontage(Animation);
}

void UUSWeaponComponent::InitAnimations()
{
    if (!EquipAnimMontage) return;

    const auto NotifyEvents = EquipAnimMontage->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishedNotify = Cast<UUSEquipFinished>(NotifyEvent.Notify);
        if (EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &UUSWeaponComponent::OnEquipFinished);
            break;
        }
    }
}

void UUSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh()) return;

    EquipAnimInProgress = false;
}

bool UUSWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress;
}
bool UUSWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}

bool UUSWeaponComponent::IsFiring() const
{
    return CurrentWeapon && CurrentWeapon->IsFiring();
}

bool UUSWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool UUSWeaponComponent::GetCurrentAmmoData(FAmmoData& CurrentAmmo) const
{
    if (CurrentWeapon)
    {
        CurrentAmmo = CurrentWeapon->GetCurrentAmmoData();
        return true;
    }
    return false;
}