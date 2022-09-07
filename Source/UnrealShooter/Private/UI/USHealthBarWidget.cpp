// UnrealShooter


#include "UI/USHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UUSHealthBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgressBar) return;
    const auto HealthBarVisibility = (Percent > PercentVisibleTreshold || FMath::IsNearlyZero(Percent))  //
                                         ? ESlateVisibility::Hidden
                                         : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = Percent > PercentColorTreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}