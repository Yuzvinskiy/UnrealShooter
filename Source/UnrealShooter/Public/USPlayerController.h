// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "USCoreTypes.h"
#include "USPlayerController.generated.h"

class UUSRespawnComponent;

UCLASS()
class UNREALSHOOTER_API AUSPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AUSPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UUSRespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;

    virtual void OnPossess(APawn* InPawn) override;

    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMatchStateChanged(EUSMatchState State);
};
