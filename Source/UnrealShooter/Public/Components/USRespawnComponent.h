// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALSHOOTER_API UUSRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UUSRespawnComponent();

	void Respawn(int32 RespawnTime);

	int32 GetRespawnCountDown() const { return RespawnCountDown; }
    bool IsRespawnInProgress() const;

	private:
    FTimerHandle RespawnTimerHandle;
        int32 RespawnCountDown = 0;

	void RespawnTimerUpdate();
 };
