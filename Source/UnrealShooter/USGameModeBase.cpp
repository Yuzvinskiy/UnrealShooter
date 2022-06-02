// UnrealShooter

#include "USGameModeBase.h"
#include "Player/USBaseCharacter.h"
#include "USPlayerController.h"
#include "UI/USGameHUD.h"

AUSGameModeBase::AUSGameModeBase()
{
    DefaultPawnClass = AUSBaseCharacter::StaticClass();
    PlayerControllerClass = AUSPlayerController::StaticClass();
    HUDClass = AUSGameHUD::StaticClass();
}
