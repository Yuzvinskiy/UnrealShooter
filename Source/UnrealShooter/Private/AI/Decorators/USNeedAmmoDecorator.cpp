// UnrealShooter


#include "AI/Decorators/USNeedAmmoDecorator.h"
#include "AIController.h"
#include "USUtils.h"
#include "Components/USWeaponComponent.h"

UUSNeedAmmoDecorator::UUSNeedAmmoDecorator() 
{
	NodeName = "NeedAmmo";
}

bool UUSNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto WeaponComponent = USUtils::GetUSPlayerComponent<UUSWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponType);

}