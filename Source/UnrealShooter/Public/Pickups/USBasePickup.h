// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class UNREALSHOOTER_API AUSBasePickup : public AActor
{
    GENERATED_BODY()

public:
    AUSBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundCue* PickupSound;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;

private:
    FTimerHandle RespawnTimerHandle;

    virtual bool GivePickupTo(APawn* PlayerPawn);
    float RotationYaw = 1.0f;
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
