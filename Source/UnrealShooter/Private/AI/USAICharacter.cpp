// UnrealShooter

#include "AI/USAICharacter.h"
#include "AI/USAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/USAIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/USHealthBarWidget.h"
#include "Components/USHealthComponent.h"

AUSAICharacter::AUSAICharacter(const FObjectInitializer& ObjInit) 
    : Super(ObjInit.SetDefaultSubobjectClass<UUSAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AUSAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AUSAICharacter::BeginPlay() 
{
    Super::BeginPlay();

    check(HealthWidgetComponent);
}

void AUSAICharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    UpdateHealthVisibility();
}

void AUSAICharacter::OnDeath() 
{
    Super::OnDeath();

    const auto USController = Cast<AAIController>(Controller);
    if (USController && USController->BrainComponent)
    {
        USController->BrainComponent->Cleanup();
    }
}

void AUSAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<UUSHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthWidgetComponent) return;
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AUSAICharacter::UpdateHealthVisibility() 
{
    if (!GetWorld() || //
        !GetWorld()->GetFirstPlayerController() || //
        GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;


    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}