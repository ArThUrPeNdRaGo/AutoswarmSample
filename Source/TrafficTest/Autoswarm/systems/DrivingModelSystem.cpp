#include "DrivingModelSystem.h"
#include <cmath>

void DrivingModelSystem::update(VehicleStorage& vehicles, SpatialGrid& spatialGrid, const std::vector<std::vector<Vector3>>& AllRoutes, float deltaTime)
{
    uint32_t count = vehicles.getMaxVehicles();

    // Exit early if no routes are generated
    if (AllRoutes.empty()) return;

    for (uint32_t i = 0; i < count; ++i) {
        // Only process vehicles in the Driving state
        if (vehicles.vehicleStates[i] != VehicleState::Driving) continue;

        // 1. Retrieve current vehicle state
        uint32_t routeIdx = vehicles.drivingStates[i].routeID;
        uint32_t targetIdx = vehicles.drivingStates[i].targetWayPoint;
        float speed = vehicles.drivingStates[i].desireSpeed;

        // Safety check: Skip if the route index is invalid or the route is empty
        if (routeIdx >= AllRoutes.size() || AllRoutes[routeIdx].empty()) continue;

        Vector3 pos = vehicles.positions[i];
        Vector3 vel = vehicles.velocities[i];
        Vector3 targetPos = AllRoutes[routeIdx][targetIdx];

        // 2. Check if the vehicle has reached the current target waypoint
        float dx = targetPos.x - pos.x;
        float dy = targetPos.y - pos.y;
        float distSq = dx * dx + dy * dy; // Squared distance

        // Consider it reached if the squared distance is less than 1000.0f
        if (distSq < 1000.0f) {
            // Update to the next waypoint (modulo for infinite looping)
            targetIdx = (targetIdx + 1) % AllRoutes[routeIdx].size();
            vehicles.drivingStates[i].targetWayPoint = targetIdx; // Write back to ECS memory

            // Fetch the new target position for the upcoming steering calculation
            targetPos = AllRoutes[routeIdx][targetIdx];
            dx = targetPos.x - pos.x;
            dy = targetPos.y - pos.y;
        }

        // 3. Calculate desired velocity (Direction * Cruise Speed)
        float dist = std::sqrt(dx * dx + dy * dy);
        Vector3 desiredVel = { 0.0f, 0.0f, 0.0f };

        if (dist > 0.001f) {
            desiredVel.x = (dx / dist) * speed;
            desiredVel.y = (dy / dist) * speed;
        }

        // 4. Calculate steering acceleration (Force = Desired Velocity - Current Velocity)
        float steerStrength = 5.0f; // Controls the sharpness of the turn
        vehicles.accelerations[i].x = (desiredVel.x - vel.x) * steerStrength;
        vehicles.accelerations[i].y = (desiredVel.y - vel.y) * steerStrength;
        vehicles.accelerations[i].z = 0.0f; // Z-axis remains flat for 2D traffic
    }
};