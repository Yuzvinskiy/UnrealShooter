// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USCoreTypes.h"
#include "USLevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class UNREALSHOOTER_API UUSLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()
	

		public:
    FOnLevelSelectedSignature OnLevelSelected;

	void SetLevelData(FLevelData& Data);

	FLevelData GetLevelData() const { return LevelData; }

	void SetSelected(bool IsSelected);

		protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock;

	UPROPERTY(meta = (BindWidget))
    UImage* LevelImage = nullptr;

	UPROPERTY(meta = (BindWidget))
    UImage* ImageFrame;

	virtual void NativeOnInitialized() override;

private:
    FLevelData LevelData;

	UFUNCTION()
    void OnLevelItemClicked();
    UFUNCTION()
    void OnLevelItemHovered();
    UFUNCTION()
    void OnLevelItemUnhovered();
};
