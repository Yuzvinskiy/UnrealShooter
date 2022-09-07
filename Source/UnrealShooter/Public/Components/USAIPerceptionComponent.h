// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "USAIPerceptionComponent.generated.h"



UCLASS()
class UNREALSHOOTER_API UUSAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
		public:
    AActor* GetClosestEnemy()const;
};
