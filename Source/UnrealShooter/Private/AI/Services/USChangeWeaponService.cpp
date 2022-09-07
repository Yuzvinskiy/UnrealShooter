// UnrealShooter


#include "AI/Services/USChangeWeaponService.h"
#include "Components/USWeaponComponent.h"
#include "AIController.h"
#include "USUtils.h"

UUSChangeWeaponService::UUSChangeWeaponService() 
{
    NodeName = "Change Weapon";
}

void UUSChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
    const auto WeaponComponent = USUtils::GetUSPlayerComponent<UUSWeaponComponent>(Controller->GetPawn());
    if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability) 
    {
        WeaponComponent->NextWeapon();
     }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

