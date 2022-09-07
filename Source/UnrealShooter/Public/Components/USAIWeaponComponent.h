// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Components/USWeaponComponent.h"
#include "USAIWeaponComponent.generated.h"


UCLASS()
class UNREALSHOOTER_API UUSAIWeaponComponent : public UUSWeaponComponent
{
	GENERATED_BODY()
	
		public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
