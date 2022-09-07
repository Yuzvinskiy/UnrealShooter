// UnrealShooter


#include "Menu/USMenuGameModeBase.h"
#include "Menu/USMenuPlayerController.h"
#include "Menu/USMenuHUD.h"

AUSMenuGameModeBase::AUSMenuGameModeBase() 
{
    PlayerControllerClass = AUSMenuPlayerController::StaticClass();
    HUDClass = AUSMenuHUD::StaticClass();
}