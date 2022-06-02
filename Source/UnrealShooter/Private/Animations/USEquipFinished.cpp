// UnrealShooter


#include "Animations/USEquipFinished.h"

void UUSEquipFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}