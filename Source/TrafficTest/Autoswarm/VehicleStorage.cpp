#include "VehicleStorage.h"

void VehicleStorage::initialize(uint32_t maxVehicles, uint32_t capacity) {
	this->max_Vehicles = maxVehicles;
	this->Capacity = capacity;

	positions.resize(maxVehicles);
	velocities.resize(maxVehicles);
	accelerations.resize(maxVehicles);
	drivingStates.resize(maxVehicles);
	vehicleStates.resize(maxVehicles);

	for (uint32_t i = 0; i < maxVehicles; ++i) {
		positions[i] = { 0.0f, 0.0f, 0.0f };
		velocities[i] = { 0.0f, 0.0f, 0.0f };
		accelerations[i] = { 0.0f, 0.0f, 0.0f };
		drivingStates[i] = { 0, 0, 0.0f };
		vehicleStates[i] = VehicleState::Driving;
	}
}

