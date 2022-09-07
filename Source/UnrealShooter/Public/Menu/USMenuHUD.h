// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "USMenuHUD.generated.h"


UCLASS()
class UNREALSHOOTER_API AUSMenuHUD : public AHUD
{
	GENERATED_BODY()
	
		protected:
    virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;
};
