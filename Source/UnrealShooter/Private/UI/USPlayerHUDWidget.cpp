// UnrealShooter

#include "UI/USPlayerHUDWidget.h"
#include "Components/USHealthComponent.h"
#include "Components/USWeaponComponent.h"
#include "USUtils.h"
#include "Components/ProgressBar.h"
#include "Player/USPlayerState.h"

void UUSPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UUSPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void UUSPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = USUtils::GetUSPlayerComponent<UUSHealthComponent>(NewPawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &UUSPlayerHUDWidget::OnHealthChanged);
    }
    UpdateHealthBar();
}

void UUSPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }
    UpdateHealthBar();
}

float UUSPlayerHUDWidget::GetHealthPercent() const
{

    const auto HealthComponent = USUtils::GetUSPlayerComponent<UUSHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool UUSPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{

    const auto WeaponComponent = USUtils::GetUSPlayerComponent<UUSWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UUSPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& CurrentAmmo) const
{
    const auto WeaponComponent = USUtils::GetUSPlayerComponent<UUSWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentAmmoData(CurrentAmmo);
}

bool UUSPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = USUtils::GetUSPlayerComponent<UUSHealthComponent>(GetOwningPlayerPawn());

    return HealthComponent && !HealthComponent->IsDead();
}

bool UUSPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

int32 UUSPlayerHUDWidget::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller) return 0;

    const auto PlayerState = Cast<AUSPlayerState>(Controller->PlayerState);
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

void UUSPlayerHUDWidget::UpdateHealthBar() 
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorTreshold ? GoodColor : BadColor);
    }
}

FString UUSPlayerHUDWidget::FormatBullets(int32 BulletsNum) const 
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    auto BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

    if (SymbolsNumToAdd > 0)
    {
        BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
    }
    return BulletStr;
}