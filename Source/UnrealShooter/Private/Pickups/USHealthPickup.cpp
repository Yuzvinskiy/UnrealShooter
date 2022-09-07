// UnrealShooter

#include "Pickups/USHealthPickup.h"
#include "Components/USHealthComponent.h"
#include "USUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool AUSHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = USUtils::GetUSPlayerComponent<UUSHealthComponent>(PlayerPawn);
    if (!HealthComponent) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}