#pragma once
#include <cstdint>
#include "../VehicleStorage.h"
#include "SpatialGrid.h"

class DrivingModelSystem
{
private:

public:
	void update(VehicleStorage& vehicles, SpatialGrid& spatialGrid, const std::vector<std::vector<Vector3>>& AllRoutes, float deltaTime);
};