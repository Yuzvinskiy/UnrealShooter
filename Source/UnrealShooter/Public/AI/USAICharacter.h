// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Player/USBaseCharacter.h"
#include "USAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class UNREALSHOOTER_API AUSAICharacter : public AUSBaseCharacter
{
    GENERATED_BODY()

public:
    AUSAICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    virtual void Tick(float DeltaTime) override;

    protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthVisibilityDistance = 2000.0f;

    virtual void BeginPlay() override;

    virtual void OnDeath() override;

    virtual void OnHealthChanged(float Health, float HealthDelta)override;

    private:
    void UpdateHealthVisibility();
};
