// UnrealShooter


#include "UI/USMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "USGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "UI/USLevelItemWidget.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogUSMenuWidget, All, All)

void UUSMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UUSMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UUSMenuWidget::OnQuitGame);
    }
    InitLevelItems();
}

void UUSMenuWidget::InitLevelItems()
{
    const auto USGameInstance = GetUSGameInstance();
    if (!USGameInstance) return;

    checkf(USGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : USGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<UUSLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &UUSMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (USGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(USGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(USGameInstance->GetStartupLevel());
    }
}
void UUSMenuWidget::OnLevelSelected(const FLevelData& Data) 
{
    const auto USGameInstance = GetUSGameInstance();
    if (!USGameInstance) return;

    USGameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void UUSMenuWidget::OnStartGame() 
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void UUSMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) 
{
    if (Animation != HideAnimation) return;
    const auto USGameInstance = GetUSGameInstance();
    if (!USGameInstance) return;

    UGameplayStatics::OpenLevel(this, USGameInstance->GetStartupLevel().LevelName);
}

void UUSMenuWidget::OnQuitGame() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}


UUSGameInstance* UUSMenuWidget::GetUSGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<UUSGameInstance>();
}