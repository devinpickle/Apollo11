#include "spacecraft.h"
#include <iostream>
using namespace std;


// Setters
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

// Getters
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

