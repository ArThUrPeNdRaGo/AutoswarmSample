#include "AutoswarmSimulation.h"
#include <cmath>

void AutoswarmSimulation::initialize(uint32_t maxVehicles, uint32_t capacity) {
	vehicleStorage.initialize(maxVehicles, capacity);
	std::vector<Vector3> route0;
	int numPoints0 = 300;
	float scale = 1000.0f;
	for (int i = 0; i < numPoints0; ++i) {
		float t = i * (6.28318f / numPoints0);
		route0.push_back({ scale * std::sin(t), scale * std::sin(t) * std::cos(t), 0.0f });
	}
	AllRoutes.push_back(route0);

	for (uint32_t i = 0; i < vehicleStorage.getMaxVehicles(); ++i) {
		uint32_t startIdx = i % numPoints0;

		vehicleStorage.positions[i] = route0[startIdx];

		vehicleStorage.drivingStates[i].targetWayPoint = (startIdx + 1) % numPoints0;

		vehicleStorage.drivingStates[i].desireSpeed = 1000.0f;

		vehicleStorage.velocities[i] = { 1.0f, 1.0f, 0.0f };
	}
}

void AutoswarmSimulation::update(float deltaTime) {
	// Update the simulation logic here
	// For example, update vehicle positions based on their velocities and accelerations
	drivingSystem.update(vehicleStorage, spatialGrid, AllRoutes, deltaTime);
	movingSystem.update(vehicleStorage, deltaTime);
}