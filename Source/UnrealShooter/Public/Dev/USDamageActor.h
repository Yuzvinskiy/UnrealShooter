// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USDamageActor.generated.h"

UCLASS()
class UNREALSHOOTER_API AUSDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AUSDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.0f;
		 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFullDamage = false; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
