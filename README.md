## Project Structure

```text
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
│       │   └── VehicleStorage.h/.cpp
│       │
│       ├── Unreal/                # Unreal-facing wrapper / rendering bridge
│       │   └── TrafficActor.h/.cpp
│       │
│       ├── TrafficTest.Build.cs   # Unreal module build rules
│       ├── TrafficTest.cpp        # Module entry
│       └── TrafficTest.h
│
├── TrafficTest.Target.cs
├── TrafficTestEditor.Target.cs
└── .vsconfig
```

## High-Level Architecture

```text
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
    ├── AutoswarmSimulation
    │   - Main simulation coordinator
    │   - Owns storage and systems
    │   - Decides update order each frame
    │
    ├── VehicleStorage
    │   - Dense arrays of simulation data
    │   - positions[]
    │   - velocities[]
    │   - accelerations[]
    │   - drivingStates[]
    │   - vehicleStates[]
    │
    ├── Component.h
    │   - Defines per-vehicle data types
    │   - Vector3
    │   - Drivingstate
    │   - VehicleState
    │
    ├── DrivingModelSystem
    │   - "AI model" for traffic behavior
    │   - Chooses where each vehicle should go
    │   - Updates target waypoint / steering / acceleration
    │
    ├── MovingSystem
    │   - Physics / kinematics step
    │   - Uses acceleration to update velocity
    │   - Uses velocity to update position
    │
    ├── SpatialGrid
    │   - Spatial acceleration structure
    │   - Used for nearby-vehicle lookup
    │   - Intended for future spatial hashing / reordering
    │
    └── EntityManager
        - Stable identity layer
        - Intended for future entity ID ↔ slot mapping
        - Not yet the hot-path simulation core
```

## Per-Frame Update Flow

```text
Unreal Engine Tick
        │
        ▼
TrafficActor::Tick()
        │
        ▼
AutoswarmSimulation::update(deltaTime)
        │
        ├── DrivingModelSystem::update(...)
        │      - Decide target waypoint
        │      - Compute desired steering / acceleration
        │
        └── MovingSystem::update(...)
               - velocity += acceleration * dt
               - position += velocity * dt
        │
        ▼
TrafficActor reads VehicleStorage
        │
        ▼
Converts simulation data to Unreal transforms
        │
        ▼
InstancedStaticMeshComponent updates visible vehicles
```
