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
	return (degree / 360) * TAU;
}

double Physics::computeVelocity(double initialVelocity, double acceleration, double time)
{
	return initialVelocity //The velocity at the beginning of the time interval
		+ (acceleration * time); //The change in velocity during the time interval
}

double Physics::computePosition(double initialPosition, double initialVelocity, double acceleration, double time)
{
	return initialPosition // The position at the beginning of the time interval
		+ (initialVelocity * time) + (0.5 * acceleration * (time * time)); // The change in position during the time interval
}

// This function gets the component of the vector along the axis from which the angle is measured
// Eg: To get the horizintal component of a vector, enter the vector's angle relative to the horizontal axis.
double Physics::computeVectorComponent(double vectorMagnitude, double angle)
{
	return vectorMagnitude * cos(angle);
}

// Compute total speed from horizontal and vertical components
double Physics::computeSpeed(float vertVelocity, float horVelocity)
{
	return sqrt((vertVelocity * vertVelocity) + (horVelocity * horVelocity));
}