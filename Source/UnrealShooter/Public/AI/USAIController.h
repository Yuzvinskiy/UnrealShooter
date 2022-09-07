// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "USAIController.generated.h"

class UUSAIPerceptionComponent;
class UUSRespawnComponent;

UCLASS()
class UNREALSHOOTER_API AUSAIController : public AAIController
{
    GENERATED_BODY()

        public:
    AUSAIController();

 protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UUSAIPerceptionComponent* USAIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UUSRespawnComponent* RespawnComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

    private:
    AActor* GetFocusOnActor() const;
};
