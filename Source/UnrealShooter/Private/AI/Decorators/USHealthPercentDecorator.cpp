// UnrealShooter


#include "AI/Decorators/USHealthPercentDecorator.h"
#include "AIController.h"
#include "USUtils.h"
#include "Components/USHealthComponent.h"

UUSHealthPercentDecorator::UUSHealthPercentDecorator() 
{
    NodeName = "Health Percent";
}

bool UUSHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto HealthComponent = USUtils::GetUSPlayerComponent<UUSHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent; 
}

