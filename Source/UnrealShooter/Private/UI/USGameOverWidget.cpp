// UnrealShooter

#include "UI/USGameOverWidget.h"
#include "UnrealShooter/USGameModeBase.h"
#include "Player/USPlayerState.h"
#include "UI/USPlayersStatsWidget.h"
#include "Components/VerticalBox.h"
#include "USUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUSGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<AUSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UUSGameOverWidget::OnMatchStateChanged);
        }
    }
    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &UUSGameOverWidget::OnResetLevel);
    }
}

void UUSGameOverWidget::OnMatchStateChanged(EUSMatchState State)
{
    if (State == EUSMatchState::GameOver)
    {
        UpdatePlayersStats();
    }
}
void UUSGameOverWidget::UpdatePlayersStats()
{
    if (!GetWorld() || !PlayersStatsBox) return;

    PlayersStatsBox->ClearChildren();
 

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<AUSPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto PlayersStatsWidget = CreateWidget<UUSPlayersStatsWidget>(GetWorld(), PlayersStatsWidgetClass);
        if (!PlayersStatsWidget) continue;

        PlayersStatsWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayersStatsWidget->SetKills(USUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayersStatsWidget->SetDeaths(USUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayersStatsWidget->SetTeam(USUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayersStatsWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayersStatsWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayersStatsBox->AddChild(PlayersStatsWidget);
    }
}

void UUSGameOverWidget::OnResetLevel() 
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}