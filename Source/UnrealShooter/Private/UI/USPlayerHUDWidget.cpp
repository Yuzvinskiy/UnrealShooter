// UnrealShooter

#include "UI/USPlayerHUDWidget.h"
#include "Components/USHealthComponent.h"
#include "Components/USWeaponComponent.h"

float UUSPlayerHUDWidget::GetHealthPercent() const
{
   
    const auto HealthComponent = GetHealthComponent();
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool UUSPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{

    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UUSPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& CurrentAmmo) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentAmmoData(CurrentAmmo);
}

bool UUSPlayerHUDWidget::IsPlayerAlive() const 
{
    const auto HealthComponent = GetHealthComponent();
    return HealthComponent && !HealthComponent->IsDead();
}

bool UUSPlayerHUDWidget::IsPlayerSpectating() const 
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

UUSWeaponComponent* UUSPlayerHUDWidget::GetWeaponComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    const auto Component = Player->GetComponentByClass(UUSWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UUSWeaponComponent>(Component);
    return WeaponComponent;
}
UUSHealthComponent* UUSPlayerHUDWidget::GetHealthComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    const auto Component = Player->GetComponentByClass(UUSHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UUSHealthComponent>(Component);
    return HealthComponent;
}

