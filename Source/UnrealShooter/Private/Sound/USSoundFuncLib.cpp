// UnrealShooter


#include "Sound/USSoundFuncLib.h"
#include "Sound/SoundClass.h"

void UUSSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if (!SoundClass) return;
    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void UUSSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass) 
{
    if (!SoundClass) return;
    const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
    SetSoundClassVolume(SoundClass, NextVolume);
}