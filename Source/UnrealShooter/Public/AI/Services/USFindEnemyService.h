// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "USFindEnemyService.generated.h"


UCLASS()
class UNREALSHOOTER_API UUSFindEnemyService : public UBTService
{
	GENERATED_BODY()
	public:
    UUSFindEnemyService();

    protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
