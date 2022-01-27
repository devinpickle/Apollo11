/*****************************
 * Header File:
 *    physics
 * Author:
 *    Spencer Wadsworth, Collette Stapley, Devin Picklesimer
 * Summary:
 *    A physics class that is called to take care of computations for changing velocities, positions, etc.
 *****************************/
#pragma once

#ifndef physics_h // prevents the header from being imported multiple times
#define physics_h

class Physics
{
	
private:
	// Constants
	const double gravity = -1.625;
	const double circleConst = 6.2831853071796; // The circle constant
	const double timestep = 0.033333333333333333; // The length of one frame of the game's display


public:
	// Constructor
	Physics();

	// Getters
	inline double getGravity() { return this->gravity; }
	inline double getTimestep() { return this->timestep; }
	inline double getCircleConst() { return this->circleConst; }

	// Compute functions
	double deltaVelocity(double time, double acceleration);
	double deltaPosition(double initialVelocity, double acceleration, double time);
	double computeVectorComponent(double vectorMagnitude, double angle);
	double computeVectorMagnitude(double vertComponent, double horComponent);
};

#endif