#include "spacecraft.h"
#include <iostream>
using namespace std;


/****************************************************************************************
* Setters: All the set functions store the desired value
****************************************************************************************/
void Spacecraft::setVertPosition(double position)
{
	this->position[1] = position;
}

void Spacecraft::setHorPosition(double position)
{
	this->position[0] = position;
}

void Spacecraft::setAngle(double angle)
{
	this->angle = angle;
}

void Spacecraft::setVertVelocity(double velocity)
{
	this->velocity[1] = velocity;
}

void Spacecraft::setHorVelocity(double velocity)
{
	this->velocity[0] = velocity;
}

void Spacecraft::setSpeed(double speed)
{
	this->speed = speed;
}

/****************************************************************************************
* Getters: All the get funcitons return the desired value
****************************************************************************************/
double Spacecraft::getVertPosition()
{
	return position[1];
}

double Spacecraft::getHorPosition()
{
	return position[0];
}

double Spacecraft::getVertVelocity()
{
	return velocity[1];
}

double Spacecraft::getHorVelocity()
{
	return velocity[0];
}

double Spacecraft::getAngle()
{
	return angle;
}

double Spacecraft::getMass()
{
	return mass;
}

double Spacecraft::getThrust()
{
	return thrust;
}

double Spacecraft::getSpeed()
{
	return speed;
}

double Spacecraft::getAcceleration()
{
	return acceleration;
}