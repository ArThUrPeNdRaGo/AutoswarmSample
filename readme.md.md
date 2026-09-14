### \## Project Structure



TrafficTest/

├── Config/                         # Unreal project config files

├── Source/

│   └── TrafficTest/

│       ├── Autoswarm/             # Core traffic simulation logic

│       │   ├── systems/           # ECS-like systems that update vehicle data

│       │   │   ├── DrivingModelSystem.h/.cpp

│       │   │   ├── MovingSystem.h/.cpp

│       │   │   └── SpatialGrid.h

│       │   │

│       │   ├── AutoswarmSimulation.h/.cpp

│       │   ├── Component.h

│       │   ├── EntityManager.h/.cpp

│       │   ├── VehicleStorage.h/.cpp

│       │

│       ├── Unreal/                # Unreal-facing wrapper / rendering bridge

│       │   ├── TrafficActor.h/.cpp

│       │

│       ├── TrafficTest.Build.cs   # Unreal module build rules

│       ├── TrafficTest.cpp        # Module entry

│       └── TrafficTest.h

│

├── TrafficTest.Target.cs

├── TrafficTestEditor.Target.cs

└── .vsconfig









### \## High-Level Architecture



TrafficTest Project

│

├── Unreal Layer

│   └── TrafficActor

│       - Lives inside the Unreal world

│       - Owns the visualization component (Instanced Static Mesh)

│       - Calls simulation update every frame

│       - Pushes simulation results into Unreal transforms

│

└── Autoswarm Core

&#x20;   ├── AutoswarmSimulation

&#x20;   │   - Main simulation coordinator

&#x20;   │   - Owns storage and systems

&#x20;   │   - Decides update order each frame

&#x20;   │

&#x20;   ├── VehicleStorage

&#x20;   │   - Dense arrays of simulation data

&#x20;   │   - positions\[]

&#x20;   │   - velocities\[]

&#x20;   │   - accelerations\[]

&#x20;   │   - drivingStates\[]

&#x20;   │   - vehicleStates\[]

&#x20;   │

&#x20;   ├── Component.h

&#x20;   │   - Defines per-vehicle data types

&#x20;   │   - Vector3

&#x20;   │   - Drivingstate

&#x20;   │   - VehicleState

&#x20;   │

&#x20;   ├── DrivingModelSystem

&#x20;   │   - "AI model" for traffic behavior

&#x20;   │   - Chooses where each vehicle should go

&#x20;   │   - Updates target waypoint / steering / acceleration

&#x20;   │

&#x20;   ├── MovingSystem

&#x20;   │   - Physics / kinematics step

&#x20;   │   - Uses acceleration to update velocity

&#x20;   │   - Uses velocity to update position

&#x20;   │

&#x20;   ├── SpatialGrid

&#x20;   │   - Spatial acceleration structure

&#x20;   │   - Used for nearby-vehicle lookup

&#x20;   │   - Intended for future spatial hashing / reordering

&#x20;   │

&#x20;   └── EntityManager

&#x20;       - Stable identity layer

&#x20;       - Intended for future entity ID ↔ slot mapping

&#x20;       - Not yet the hot-path simulation core





### \## Per-Frame Update Flow



Unreal Engine Tick

&#x20;       │

&#x20;       ▼

TrafficActor::Tick()

&#x20;       │

&#x20;       ▼

AutoswarmSimulation::update(deltaTime)

&#x20;       │

&#x20;       ├── DrivingModelSystem::update(...)

&#x20;       │      - Decide target waypoint

&#x20;       │      - Compute desired steering / acceleration

&#x20;       │

&#x20;       └── MovingSystem::update(...)

&#x20;              - velocity += acceleration \* dt

&#x20;              - position += velocity \* dt

&#x20;       │

&#x20;       ▼

TrafficActor reads VehicleStorage

&#x20;       │

&#x20;       ▼

Converts simulation data to Unreal transforms

&#x20;       │

&#x20;       ▼

InstancedStaticMeshComponent updates visible vehicles

