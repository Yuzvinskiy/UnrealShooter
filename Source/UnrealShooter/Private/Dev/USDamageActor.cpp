// UnrealShooter


#include "Dev/USDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AUSDamageActor::AUSDamageActor()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}


void AUSDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void AUSDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}

