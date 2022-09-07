// UnrealShooter

#include "AI/USAIController.h"
#include "AI/USAICharacter.h"
#include "Components/USAIPerceptionComponent.h"
#include "Components/USRespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AUSAIController::AUSAIController()
{
    USAIPerceptionComponent = CreateDefaultSubobject<UUSAIPerceptionComponent>("USAIPerceptionComponent");
    SetPerceptionComponent(*USAIPerceptionComponent);

    RespawnComponent = CreateDefaultSubobject<UUSRespawnComponent>("RespawnComponent");

    bWantsPlayerState = true;
}

void AUSAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto USCharacter = Cast<AUSAICharacter>(InPawn);
    if (USCharacter)
    {
        RunBehaviorTree(USCharacter->BehaviorTreeAsset);
    }
}

void AUSAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* AUSAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}