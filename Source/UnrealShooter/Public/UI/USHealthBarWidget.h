// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class UNREALSHOOTER_API UUSHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetHealthPercent(float Percent);

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentVisibleTreshold = 0.8;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorTreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;
};
