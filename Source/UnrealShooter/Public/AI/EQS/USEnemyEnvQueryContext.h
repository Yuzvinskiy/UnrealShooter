// UnrealShooter

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "USEnemyEnvQueryContext.generated.h"


UCLASS()
class UNREALSHOOTER_API UUSEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData)const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";

};
