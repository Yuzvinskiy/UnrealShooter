// UnrealShooter


#include "AI/Services/USFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "USUtils.h"
#include "Components/USAIPerceptionComponent.h"

UUSFindEnemyService::UUSFindEnemyService() 
{
    NodeName = "Find Enemy";
}

void UUSFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if (BlackBoard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = USUtils::GetUSPlayerComponent<UUSAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }

    } 
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}