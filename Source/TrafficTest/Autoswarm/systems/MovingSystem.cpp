#include "MovingSystem.h"
#include <cstdint>
#include <cmath>

void MovingSystem::update(VehicleStorage& vehicles, float deltaTime)
{
    uint32_t count = vehicles.getMaxVehicles();

    for (uint32_t i = 0; i < count; ++i) {
        if (vehicles.vehicleStates[i] != VehicleState::Driving) continue;

        // 1. Update velocity based on acceleration (Euler Integration: V = V + A * dt)
        vehicles.velocities[i].x += vehicles.accelerations[i].x * deltaTime;
        vehicles.velocities[i].y += vehicles.accelerations[i].y * deltaTime;
        vehicles.velocities[i].z += vehicles.accelerations[i].z * deltaTime;

        // 2. Update position based on velocity (P = P + V * dt)
        vehicles.positions[i].x += vehicles.velocities[i].x * deltaTime;
        vehicles.positions[i].y += vehicles.velocities[i].y * deltaTime;
        vehicles.positions[i].z += vehicles.velocities[i].z * deltaTime;

        // 3. CRITICAL: Clear acceleration for the next frame
        // Otherwise, previous steering forces will accumulate and send the vehicle flying
        vehicles.accelerations[i] = { 0.0f, 0.0f, 0.0f };
    }
}