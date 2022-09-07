// UnrealShooter


#include "Components/USRespawnComponent.h"
#include "UnrealShooter/USGameModeBase.h"


UUSRespawnComponent::UUSRespawnComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	
}

void UUSRespawnComponent::Respawn(int32 RespawnTime) 
{
    if (!GetWorld())return;
    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UUSRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void UUSRespawnComponent::RespawnTimerUpdate() 
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<AUSGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}

bool UUSRespawnComponent::IsRespawnInProgress() const 
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}
