#pragma once
#include <cstdint>
#include <vector>
#include "VehicleStorage.h"
#include "./systems/DrivingModelSystem.h"
#include "./systems/MovingSystem.h"

class AutoswarmSimulation
{
private:
	

	DrivingModelSystem drivingSystem;
	MovingSystem movingSystem;
	SpatialGrid spatialGrid;

public:
	void initialize(uint32_t maxVehicles, uint32_t capacity);
	VehicleStorage vehicleStorage;
	void update(float deltaTime);
	std::vector<std::vector<Vector3>> AllRoutes;

};
