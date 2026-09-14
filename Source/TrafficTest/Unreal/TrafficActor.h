#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "../Autoswarm/AutoswarmSimulation.h" 
#include "TrafficActor.generated.h"

UCLASS()
class TRAFFICTEST_API ATrafficActor : public AActor
{
    GENERATED_BODY()

public:
    ATrafficActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* SceneRoot;

    UPROPERTY(VisibleAnywhere)
    UInstancedStaticMeshComponent* InstancedMesh;

private:
    AutoswarmSimulation Simulation;
};