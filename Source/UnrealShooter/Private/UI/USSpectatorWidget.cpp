// UnrealShooter

#include "UI/USSpectatorWidget.h"
#include "USUtils.h"
#include "Components/USRespawnComponent.h"

bool UUSSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = USUtils::GetUSPlayerComponent<UUSRespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();

    return true;
}