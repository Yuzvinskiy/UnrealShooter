// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USCoreTypes.h"
#include "USWeaponFXComponent.generated.h"



class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALSHOOTER_API UUSWeaponFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UUSWeaponFXComponent();

  void PlayImpactFX(const FHitResult& Hit);

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "VFX")
  FImpactData DefaultImpactData;

  UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "VFX")
  TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
