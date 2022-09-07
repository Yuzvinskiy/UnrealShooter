// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "USMenuPlayerController.generated.h"


UCLASS()
class UNREALSHOOTER_API AUSMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
		protected:
    virtual void BeginPlay() override;
};
