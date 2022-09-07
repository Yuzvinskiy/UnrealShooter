// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "USHealthPercentDecorator.generated.h"


UCLASS()
class UNREALSHOOTER_API UUSHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
	public:
    UUSHealthPercentDecorator();

    protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
