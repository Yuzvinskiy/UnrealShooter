// UnrealShooter


#include "UI/USPlayersStatsWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UUSPlayersStatsWidget::SetPlayerName(const FText& Text)
{
    if (!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}
void UUSPlayersStatsWidget::SetKills(const FText& Text) 
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}
void UUSPlayersStatsWidget::SetDeaths(const FText& Text) 
{
    if (!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}
void UUSPlayersStatsWidget::SetTeam(const FText& Text) 
{
    if (!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}
void UUSPlayersStatsWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UUSPlayersStatsWidget::SetTeamColor(const FLinearColor& Color)
{
    if (!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
