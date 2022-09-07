// UnrealShooter


#include "Menu/USMenuPlayerController.h"
#include "USGameInstance.h"

void AUSMenuPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;

    
}