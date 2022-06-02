// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "USGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHOOTER_API AUSGameHUD : public AHUD
{
	GENERATED_BODY()

	public:
    virtual void DrawHUD() override;

	protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;

    private: 
	void DrawCrosshair();
};
