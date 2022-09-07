// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "UI/MyBaseWidget.h"
#include "USPauseWidget.generated.h"

class UButton;

UCLASS()
class UNREALSHOOTER_API UUSPauseWidget : public UMyBaseWidget
{
	GENERATED_BODY()
	


	protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;

	private:
    UFUNCTION()
    void OnClearPause();

};
