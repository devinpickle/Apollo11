#include "spacecraft.h"
#include "physics.h"
#include <iostream>
using namespace std;


Spacecraft::Spacecraft()
{
	acceleration = 15103 / 45000;
	fuel = 3000;
	status = FlightStatus::flying;
	if (status == FlightStatus::flying)
	Physics p;
	angle = 0;
}

Spacecraft::Spacecraft(const Point& pos, const Point& vel) :
	position(pos),
	velocity(vel),
	angle(0.0),
	acceleration(15103.0 / 45000.0),
	fuel(3000.0),
	status(FlightStatus::flying),
	p()
{
	
}

	


/****************************************************************************************
* Setters: All the set functions store the desired value
****************************************************************************************/
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


/****************************************************************************************
* Getters: All the get functions return the desired value
****************************************************************************************/
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

void Spacecraft::updateVertPosition(bool mainThrust)
{
	this->position.addY(p.deltaPosition(
		this->velocity.getY(), // The ship's vertical velocity at the beginning of the time interval
		p.computeVectorComponent(this->acceleration, this->angle) * mainThrust + p.getGravity(), // The ship's acceleration durring the time interval
		p.getTimestep() // The time interval
	));
}

void Spacecraft::updateHorPosition(bool mainThrust)
{
	this->position.addX(p.deltaPosition(
		this->velocity.getX(), // The ship's vertical velocity at the beginning of the time interval
		p.computeVectorComponent(this->acceleration, this->angle - p.getCircleConst()/4) * mainThrust, // The ship's acceleration durring the time interval
		p.getTimestep() // The time interval
	));
}

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

void Spacecraft::updateVertVelocity(bool mainThrust)
{
	this->velocity.addY(p.deltaVelocity(
		p.computeVectorComponent(this->acceleration, this->angle) * mainThrust + p.getGravity(), // The ship's acceleration durring the time interval
		p.getTimestep() // The time interval
	));
}

void Spacecraft::updateHorVelocity(bool mainThrust)
{
	this->velocity.addX(p.deltaVelocity(
		p.computeVectorComponent(this->acceleration, this->angle - p.getCircleConst() / 4) * mainThrust, // The ship's acceleration durring the time interval
		p.getTimestep() // The time interval
	));
}

void Spacecraft::updateFuel(bool mainThrust)
{
	if (mainThrust)
	{
		this->fuel -= 0.1;
	}

}

void Spacecraft::updateStatus(FlightStatus stat)
{
	this->status = stat;
}
