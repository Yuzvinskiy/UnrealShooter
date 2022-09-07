// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "USSoundFuncLib.generated.h"

class USoundClass;

UCLASS()
class UNREALSHOOTER_API UUSSoundFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
		public:
    UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintCallable)
    static void ToggleSoundClassVolume(USoundClass* SoundClass);
};
