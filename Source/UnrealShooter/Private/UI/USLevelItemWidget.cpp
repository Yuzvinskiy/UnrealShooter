// UnrealShooter

#include "UI/USLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UUSLevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &UUSLevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &UUSLevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &UUSLevelItemWidget::OnLevelItemUnhovered);
    }
}



void UUSLevelItemWidget::SetLevelData(FLevelData& Data) 
{
    LevelData = Data;
    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    }
    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumbnail);
    }
}

void UUSLevelItemWidget::SetSelected(bool IsSelected) 
{
    if (LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}
void UUSLevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}
void UUSLevelItemWidget::OnLevelItemHovered()
{
    if (ImageFrame)
    {
        ImageFrame->SetVisibility(ESlateVisibility::Visible);
    }
}

void UUSLevelItemWidget::OnLevelItemUnhovered() 
{
    if (ImageFrame)
    {
        ImageFrame->SetVisibility(ESlateVisibility::Hidden);
    }
}