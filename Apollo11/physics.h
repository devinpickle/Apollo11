#pragma once

#ifndef physics_h // prevents the header from being imported multiple times
#define physics_h

class Physics
{
public:
	

	// Getters
	double getGravity();

	// Compute functions
	double computeRadians(double degree);
	double computeVelocity(double initialVelocity, double time, double acceleration);
	double computePosition(double initialPosition, double initialVelocity, double acceleration, double time);
	double computeAcceleration(double angle, double netAcceleration);
	double computeSpeed(float vertVel, float horVel);


private:
	double gravity = 1.625;
	double radians;

};

#endif