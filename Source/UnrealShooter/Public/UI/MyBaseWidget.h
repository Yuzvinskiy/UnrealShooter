// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyBaseWidget.generated.h"

class USoundCue;

UCLASS()
class UNREALSHOOTER_API UMyBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
		public:
    void Show();

		protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* OpenSound;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;
};
