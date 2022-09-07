// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "UI/MyBaseWidget.h"
#include "USCoreTypes.h"
#include "USGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class UNREALSHOOTER_API UUSGameOverWidget : public UMyBaseWidget
{
    GENERATED_BODY()



protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayersStatsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayersStatsWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(EUSMatchState State);
    void UpdatePlayersStats();

    UFUNCTION()
    void OnResetLevel();
};
