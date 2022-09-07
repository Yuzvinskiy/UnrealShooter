// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameDataWidget.generated.h"

class AUSGameModeBase;
class AUSPlayerState;

UCLASS()
class UNREALSHOOTER_API UGameDataWidget : public UUserWidget
{
    GENERATED_BODY()

public:


    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundTimeRemaining() const;

private:
    AUSGameModeBase* GetUSGameMode() const;
    AUSPlayerState* GetUSPlayerState() const;
};
