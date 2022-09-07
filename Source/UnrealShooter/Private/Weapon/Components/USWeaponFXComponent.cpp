// UnrealShooter

#include "Weapon/Components/USWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/DecalComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

UUSWeaponFXComponent::UUSWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    auto ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

    //decals
   auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),  //
        ImpactData.DecalData.Material,                  //
        ImpactData.DecalData.Size,                      //
        Hit.ImpactPoint,                                //
        Hit.ImpactPoint.Rotation());

    if (DecalComponent)
   {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
   }

    //sound 
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.ImpactSound, Hit.ImpactPoint);
    
}
