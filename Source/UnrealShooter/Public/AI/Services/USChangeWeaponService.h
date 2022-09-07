// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "USChangeWeaponService.generated.h"


UCLASS()
class UNREALSHOOTER_API UUSChangeWeaponService : public UBTService
{
	GENERATED_BODY()
public:
    UUSChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
