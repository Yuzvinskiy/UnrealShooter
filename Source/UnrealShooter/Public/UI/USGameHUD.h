// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "USCoreTypes.h"
#include "USGameHUD.generated.h"

class UMyBaseWidget;

UCLASS()
class UNREALSHOOTER_API AUSGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

      UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

      UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<EUSMatchState, UMyBaseWidget*> GameWidgets;

    UPROPERTY()
    UMyBaseWidget* CurrentWidget = nullptr;

    void DrawCrosshair();
    void OnMatchStateChanged(EUSMatchState State);
};
