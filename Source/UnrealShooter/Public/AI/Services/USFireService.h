// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "USFireService.generated.h"


UCLASS()
class UNREALSHOOTER_API UUSFireService : public UBTService
{
	GENERATED_BODY()
	public:
    UUSFireService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
