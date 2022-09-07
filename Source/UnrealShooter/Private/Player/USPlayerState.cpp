// UnrealShooter


#include "Player/USPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogUSPlayerState, All, All)

void AUSPlayerState::LogInfo() 
{
    UE_LOG(LogUSPlayerState, Display, TEXT("TeamID: %i, Kills num: %i, Deaths num: %i"), TeamID, KillsNum, DeathsNum);
}