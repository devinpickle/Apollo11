/********************************************************************
 * Header File:
 *    spacecraft
 * Author:
 *    Spencer Wadsworth, Devin Picklesimer, Collette Stapley
 * Summary:
 *    Designed to represent the lunar module; Keeps track of its own 
 *	  position, velocity, angle, etc.
 ********************************************************************/

#include "spacecraft.h"
#include "physics.h"
#include <iostream>
using namespace std;


Spacecraft::Spacecraft()
{
	acceleration = (15103 / 45000) * 100;
	fuel = 5000.0;
	status = FlightStatus::flying;
	if (status == FlightStatus::flying)
	Physics p;
	angle = 0;
}

Spacecraft::Spacecraft(const Point& pos, const Point& vel) :
	position(pos),
	velocity(vel),
	angle(0.0),
	acceleration((15103.0 / 45000.0) * 100),
	fuel(5000.0),
	status(FlightStatus::flying),
	p()
{
	
}

	


/********************************************************************
* Setters: All the set functions store the desired value
*********************************************************************/
void Spacecraft::setVertPosition(double pos)
{
	this->position.setY(pos);
}

void Spacecraft::setHorPosition(double pos)
{
	this->position.setX(pos);
}

void Spacecraft::setAngle(double ang)
{
	this->angle = ang;
}

void Spacecraft::setVertVelocity(double vel)
{
	this->velocity.setY(vel);
}

void Spacecraft::setHorVelocity(double vel)
{
	this->velocity.setX(vel);
}


/********************************************************************
* Getters: All the get functions return the desired value
*********************************************************************/
Point Spacecraft::getPosition()
{
	return position;
}

Point Spacecraft::getVelocity()
{
	return velocity;
}

double Spacecraft::getAngle()
{
	return angle;
}

double Spacecraft::getAcceleration()
{
	return acceleration;
}

double Spacecraft::getFuel()
{
	return fuel;
}

double Spacecraft::getSpeed()
{
	return p.computeVectorMagnitude(velocity.getY(), velocity.getX());
}

/********************************************************************
 * UpdateVertPosition
 * Updates the vertical position of the spacecraft if main thrusters 
 * are on
 ********************************************************************/
void Spacecraft::updateVertPosition(bool mainThrust)
{
	this->position.addY(p.deltaPosition(
		this->velocity.getY(), // The ship's vertical velocity at the beginning of the time interval
		(p.computeVectorComponent(this->acceleration, this->angle) * mainThrust) + p.getGravity(), // The ship's acceleration durring the time interval
		p.getTimestep() // The time interval
	));
	
}

/********************************************************************
 * UpdateHorPosition
 * Updates the horizontal position of the spacecraft if main thrusters
 * are on
 ********************************************************************/
void Spacecraft::updateHorPosition(bool mainThrust)
{
	this->position.addX((p.deltaPosition(
		this->velocity.getX(), // The ship's vertical velocity at the beginning of the time interval
		p.computeVectorComponent(this->acceleration, this->angle - p.getCircleConst()/4) * mainThrust, // The ship's acceleration durring the time interval
		p.getTimestep() // The time interval
	) * -1));
	
}

/********************************************************************
 * UpdateAngle
 * Updates the angle of the spacecraft based on side thruster activity
 ********************************************************************/
void Spacecraft::updateAngle(bool leftThrust, bool rightThrust)
{
	if (leftThrust)
	{
		this->angle -= 0.1;
	}

	if (rightThrust)
	{
		this->angle += 0.1;
	}

}

/********************************************************************
 * UpdateVertVelocity
 * Updates the vertical velocity of the spacecraft if main thrusters
 * are on
 ********************************************************************/
void Spacecraft::updateVertVelocity(bool mainThrust)
{
	this->velocity.addY(p.deltaVelocity(
		p.computeVectorComponent(this->acceleration, this->angle) * mainThrust + p.getGravity(), // The ship's acceleration durring the time interval
		p.getTimestep() // The time interval
	));
}

/********************************************************************
 * UpdateHorVelocity
 * Updates the horizontal velocity of the spacecraft if main thrusters
 * are on
 ********************************************************************/
void Spacecraft::updateHorVelocity(bool mainThrust)
{
	this->velocity.addX(p.deltaVelocity(
		p.computeVectorComponent(this->acceleration, this->angle - p.getCircleConst() / 4) * mainThrust, // The ship's acceleration durring the time interval
		p.getTimestep() // The time interval
	));
}

/********************************************************************
 * UpdateFuel
 * Fuel depletes if main thrusters are active
 ********************************************************************/
void Spacecraft::updateFuel(bool mainThrust, bool leftThrust, bool rightThrust)
{
	if (mainThrust)
		this->fuel -= 10;
	if (leftThrust)
		this->fuel -= 1;
	if (rightThrust)
		this->fuel -= 1;


}

/********************************************************************
 * UpdateStatus
 * Change the status of the spacecraft
 ********************************************************************/
void Spacecraft::updateStatus(FlightStatus stat)
{
	this->status = stat;
}
