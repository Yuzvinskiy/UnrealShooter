// UnrealShooter

#include "UI/USGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/MyBaseWidget.h"
#include "UnrealShooter/USGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogUSGameHUD, All, All);

void AUSGameHUD::DrawHUD()
{
    Super::DrawHUD();
    //DrawCrosshair();
}

void AUSGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EUSMatchState::InProgress, CreateWidget<UMyBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EUSMatchState::Pause, CreateWidget<UMyBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EUSMatchState::GameOver, CreateWidget<UMyBaseWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AUSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AUSGameHUD::OnMatchStateChanged);
        }
    }
}

void AUSGameHUD::OnMatchStateChanged(EUSMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }

    UE_LOG(LogUSGameHUD, Display, TEXT("Matchstate is changed: %s"), *UEnum::GetValueAsString(State));
}

void AUSGameHUD::DrawCrosshair()
{

    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;
}