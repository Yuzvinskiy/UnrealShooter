// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USCoreTypes.h"
#include "USPlayerHUDWidget.generated.h"

class UUSWeaponComponent;
class UUSHealthComponent;

UCLASS()
class UNREALSHOOTER_API UUSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentAmmoData(FAmmoData& CurrentAmmo) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

	private: 
	UUSWeaponComponent* GetWeaponComponent() const;
        UUSHealthComponent* GetHealthComponent() const;
};
