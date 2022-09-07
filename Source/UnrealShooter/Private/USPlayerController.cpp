// UnrealShooter


#include "USPlayerController.h"
#include "Components/USRespawnComponent.h"
#include "UnrealShooter/USGameModeBase.h"

AUSPlayerController::AUSPlayerController() 
{
    RespawnComponent = CreateDefaultSubobject<UUSRespawnComponent>("RespawnComponent");
}

 void AUSPlayerController::BeginPlay() 
 {
     Super::BeginPlay();

         if (GetWorld())
     {
         const auto GameMode = Cast<AUSGameModeBase>(GetWorld()->GetAuthGameMode());
         if (GameMode)
         {
             GameMode->OnMatchStateChanged.AddUObject(this, &AUSPlayerController::OnMatchStateChanged);
         }
     }
 }

 void AUSPlayerController::OnMatchStateChanged(EUSMatchState State) 
 {
     if (State == EUSMatchState::InProgress)
     {
         SetInputMode(FInputModeGameOnly());
         bShowMouseCursor = false;
     }
     else
     {
         SetInputMode(FInputModeUIOnly());
         bShowMouseCursor = true;
     }
 }

void AUSPlayerController::OnPossess(APawn* InPawn) 
{
    Super::OnPossess(InPawn);
    
    OnNewPawn.Broadcast(InPawn);
}

void AUSPlayerController::SetupInputComponent() 
{
    Super::SetupInputComponent();

    if(!InputComponent) return;
    InputComponent->BindAction("Pause Game", IE_Pressed, this, &AUSPlayerController::OnPauseGame);
}


void AUSPlayerController::OnPauseGame()
{
    if (!GetWorld() && !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this); 
}