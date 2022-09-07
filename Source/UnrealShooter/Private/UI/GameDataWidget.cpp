// UnrealShooter

#include "UI/GameDataWidget.h"
#include "UnrealShooter/USGameModeBase.h"
#include "Player/USPlayerState.h"


int32 UGameDataWidget::GetCurrentRoundNum() const 
{
    const auto GameMode = GetUSGameMode();
    return GameMode ? GameMode->GetCurrentRoundName() : 0;
}
int32 UGameDataWidget::GetTotalRoundsNum() const 
{
    const auto GameMode = GetUSGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}
int32 UGameDataWidget::GetRoundTimeRemaining() const 
{
    const auto GameMode = GetUSGameMode();
    return GameMode ? GameMode->GetRoundTimeRemaining() : 0;
}

AUSGameModeBase* UGameDataWidget::GetUSGameMode() const
{
    return GetWorld() ? Cast<AUSGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}
AUSPlayerState* UGameDataWidget::GetUSPlayerState() const
{
    return GetOwningPlayer() ? Cast<AUSPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}