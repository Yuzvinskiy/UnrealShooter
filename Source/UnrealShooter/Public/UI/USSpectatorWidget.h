// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USSpectatorWidget.generated.h"


UCLASS()
class UNREALSHOOTER_API UUSSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()
	
		public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32& CountDownTime) const;
};
