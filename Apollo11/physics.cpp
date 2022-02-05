/********************************************************************
 * Header File:
 *    physics
 * Author:
 *    Spencer Wadsworth, Collette Stapley, Devin Picklesimer
 * Summary:
 *    A physics class that is called to take care of computations for
 *	  changing velocities, positions, etc.
 *********************************************************************/

#include "physics.h"
#include <iostream>

using namespace std;

/****************************************************************************************
* Compute functions
****************************************************************************************/

/****************************************************************************************
* This function calcluated the change in Velocity
****************************************************************************************/
double Physics::deltaVelocity(double acceleration, double time)
{
	return acceleration * time; // The change in velocity during the time interval
}

/****************************************************************************************
* This function computes thecahnge in the object's position
****************************************************************************************/
double Physics::deltaPosition(double initialVelocity, double acceleration, double time)
{
	return (initialVelocity * time) + (0.5 * acceleration * (time * time)); // The change in position during the time interval
}

/****************************************************************************************
* This function gets the component of the vector along the axis from which the angle is measured
* Eg: To get the horizintal component of a vector, enter the vector's angle relative to the horizontal axis.
****************************************************************************************/
double Physics::computeVectorComponent(double vectorMagnitude, double angle)
{
	return vectorMagnitude * cos(angle);
}

/****************************************************************************************
* Compute a vector's magnitude from horizontal and vertical components
****************************************************************************************/
double Physics::computeVectorMagnitude(double vertComponent, double horComponent)
{
	return sqrt((vertComponent * vertComponent) + (horComponent * horComponent));
}