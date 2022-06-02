// UnrealShooter

#include "Weapon/USLuncherWeapon.h"
#include "Weapon/USProjectile.h"

void AUSLuncherWeapon::StartFire()
{
    Super::StartFire();
    MakeShot();
}

void AUSLuncherWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    AUSProjectile* Projectile = GetWorld()->SpawnActorDeferred<AUSProjectile>(ProjectileClass, SpawnTransform);

    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    StopFire();
}