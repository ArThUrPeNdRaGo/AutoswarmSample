#pragma once
#include <cstdint>

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Drivingstate {
	uint32_t routeID = 0;
	uint32_t targetWayPoint = 0;
	float desireSpeed = 0;
};

enum class VehicleState: uint8_t
{
	Driving,
	Crashed,
	Respawning
};


	

