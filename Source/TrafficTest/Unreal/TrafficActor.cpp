// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficActor.h"

// Sets default values
ATrafficActor::ATrafficActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	InstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	InstancedMesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void ATrafficActor::BeginPlay()
{
	Super::BeginPlay();
	uint32_t numVehicles = 1;
	Simulation.initialize(numVehicles, numVehicles);

	for (uint32_t i = 0; i < numVehicles; ++i)
	{
		InstancedMesh->AddInstance(FTransform::Identity);
	}
}

// Called every frame
void ATrafficActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Simulation.update(DeltaTime);

    uint32_t count = Simulation.vehicleStorage.getMaxVehicles();
    for (uint32_t i = 0; i < count; ++i)
    {
		Vector3 pos = Simulation.vehicleStorage.positions[i];
		Vector3 vel = Simulation.vehicleStorage.velocities[i];

		FVector UEPos(pos.x, pos.y, pos.z);
		FRotator UERot = FVector(vel.x, vel.y, vel.z).Rotation();

		FVector UEScale(1.0f, 1.0f, 1.0f);

		FTransform NewTransform(UERot, UEPos, UEScale);
		InstancedMesh->UpdateInstanceTransform(i, NewTransform, false, false, false);
    }

    InstancedMesh->MarkRenderStateDirty();

}

