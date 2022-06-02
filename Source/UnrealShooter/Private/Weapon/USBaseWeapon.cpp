
#include "Weapon/USBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AUSBaseWeapon::AUSBaseWeapon()
{

    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AUSBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
    
    CurrentAmmo = DefaultAmmo;
}

void AUSBaseWeapon::StartFire() 
{
    FireInProgress = true;
}
void AUSBaseWeapon::StopFire() 
{
    FireInProgress = false;
}

bool AUSBaseWeapon::IsFiring() const 
{
    return FireInProgress;
}

void AUSBaseWeapon::MakeShot() {}

APlayerController* AUSBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool AUSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector AUSBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AUSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void AUSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

 void AUSBaseWeapon::DecreaseAmmo() 
 {
     CurrentAmmo.Bullets--;
     LogAmmo();
     if (IsClipEmpty() && !IsAmmoEmpty())
     {
         ChangeClip();
     }
 }
bool AUSBaseWeapon::IsAmmoEmpty() const 
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}
 bool AUSBaseWeapon::IsClipEmpty() const 
 {
     return CurrentAmmo.Bullets == 0;
 }
void AUSBaseWeapon::ChangeClip() 
{
    CurrentAmmo.Bullets = DefaultAmmo.Bullets; 
    if (!CurrentAmmo.Infinite)
    {
        CurrentAmmo.Clips--;
    }
    UE_LOG(LogBaseWeapon, Display, TEXT("_____Change Clip____"));
}
 void AUSBaseWeapon::LogAmmo() 
 {
     FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
     AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
     UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
 }