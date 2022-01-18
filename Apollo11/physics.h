#pragma once

#ifndef physics_h // prevents the header from being imported multiple times
#define physics_h

class Physics
{
public:
	
	// Constants
	double const circleConst = 6.2831853071796; // The circle constant

	// Getters
	double getGravity();
	double getRadians();

	// Setters
	void setRadians(double radians);

	// Constructor
	Physics();

	// Compute functions
	double computeRadians(double degree);
	double computeVelocity(double initialVelocity, double time, double acceleration);
	double computePosition(double initialPosition, double initialVelocity, double acceleration, double time);
	double computeVectorComponent(double vectorMagnitude, double angle);
	double computeSpeed(double vertVel, double horVel);


private:
	const double gravity = -1.625;
	double radians;

};

#endif