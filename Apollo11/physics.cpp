#include "physics.h"
#include <iostream>

using namespace std;


// Getters
double Physics::getGravity()
{
	return this->gravity;
}

// Compute functions
double Physics::computeRadians(double degree)
{
	return 0;
}
double Physics::computeVelocity(double initialVelocity, double time, double acceleration)
{
	return 0;
}
double Physics::computePosition(double initialPosition, double initialVelocity, double acceleration, double time)
{
	return 0;
}
double Physics::computeAcceleration(double angle, double netAcceleration)
{
	return 0;
}

double Physics::computeSpeed(float vertVel, float horVel) {
	// Compute total velocity at landing
	float totalVelocity = sqrt((vertVel * vertVel) + (horVel * horVel));
	return totalVelocity;
}