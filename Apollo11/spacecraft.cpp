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
#include <iomanip>
using namespace std;


Spacecraft::Spacecraft()
{
	acceleration = (15103.0 / 45000.0) * 100;
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

/**********************************************************************
	 * drawSpacecraft
	 * Draws lunar lander and its status on the screen
**********************************************************************/
void Spacecraft::drawSpacecraft(ogstream & gout, Ground & ground)
{
	// draw the lander and its flames
	gout.drawLander(this->position /*position*/, this->angle /*angle*/);

	// draw stats which are part of spacecraft
	// put some text on the screen
	gout.setPosition(Point(5.0, 380.0));
	gout << "Fuel: " << this->fuel << "\n" <<
		"Altitude: " << fixed << setprecision(0) << ground.getElevation(this->position) << " meters" << "\n" <<
		"Speed: " << fixed << setprecision(2) << this->getSpeed() << " m/s";
	
}

/**********************************************************************
	 * updateSpacecraft
	 * Updates all properties of spacecraft based on status
	 * and fuel
**********************************************************************/
void Spacecraft::updateSpacecraft(const Interface* pUI, ogstream& gout)
{
	if (getStatus() == FlightStatus::flying) {
		if (getFuel() > 0) {
			updateAngle(pUI->isLeft(), pUI->isRight());
			updateFuel(pUI->isDown(), pUI->isLeft(), pUI->isRight());
			updateHorPosition(pUI->isDown());
			updateVertPosition(pUI->isDown());
			updateHorVelocity(pUI->isDown());
			updateVertVelocity(pUI->isDown());
			// Draw lander flames if fuel is available
			gout.drawLanderFlames(getPosition(), getAngle(), /*angle*/
				pUI->isDown(), pUI->isLeft(), pUI->isRight());
		}
		else {
			updateHorPosition(false);
			updateVertPosition(false);
			updateHorVelocity(false);
			updateVertVelocity(false);
		}
	}
}

void Spacecraft::checkCollisions(Ground & ground, ogstream & gout)
{
	if (ground.onPlatform(getPosition(), 20))
	{
		if (abs(getAngle()) <= 0.3 && getSpeed() <= 4.0)
			updateStatus(FlightStatus::landed);
		else
			updateStatus(FlightStatus::crashed);
	}
	else if (ground.hitGround(getPosition(), 20))
		updateStatus(FlightStatus::crashed);

	switch (getStatus())
	{
	case FlightStatus::landed:
		setAngle(0.0);
		gout.setPosition(Point(200.0, 380.0));
		gout << "The Eagle has landed!";
		break;
	case FlightStatus::crashed:
		setAngle(3.14);
		gout.setPosition(Point(200.0, 380.0));
		gout << "Houston We Have A Problem";
		break;
	}
}