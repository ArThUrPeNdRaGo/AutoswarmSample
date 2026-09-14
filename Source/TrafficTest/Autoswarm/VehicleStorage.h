#pragma once
#include <cstdint>
#include <vector>
#include "Component.h"


class VehicleStorage {
private:
	uint32_t max_Vehicles = 0;
	uint32_t Capacity = 0;
public:
	void initialize(uint32_t maxVehicles, uint32_t capacity);

	uint32_t getMaxVehicles() const {
		return max_Vehicles;
	};

	uint32_t getCapacity() const {
		return Capacity;
	};

	std::vector<Vector3> positions;
	std::vector<Vector3> velocities;
	std::vector<Vector3> accelerations;
	std::vector<Drivingstate> drivingStates;
	std::vector<VehicleState> vehicleStates;

};
