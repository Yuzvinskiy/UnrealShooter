// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "USNeedAmmoDecorator.generated.h"

class AUSBaseWeapon;

UCLASS()
class UNREALSHOOTER_API UUSNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
		public:
    UUSNeedAmmoDecorator();

	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AUSBaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
