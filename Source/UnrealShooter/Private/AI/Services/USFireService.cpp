// UnrealShooter

#include "AI/Services/USFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "USUtils.h"
#include "Components/USWeaponComponent.h"

UUSFireService::UUSFireService()
{
    NodeName = "Fire";
}

void UUSFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller) 
    {
        const auto WeaponComponent = USUtils::GetUSPlayerComponent<UUSWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
