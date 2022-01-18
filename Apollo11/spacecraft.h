/*****************************
 * Header File:
 *    spacecraft
 * Author:
 *    Spencer Wadsworth, Devin Picklesimer, Collette Stapley
 * Summary:
 *    Designed to represent the lunar module; Keeps track of its own position, velocity, angle, etc.
 *****************************/
#pragma once


#ifndef spacecraft_h // prevents the header from being imported multiple times
#define spacecraft_h

class Spacecraft
{
public:
	// Constructor
	Spacecraft()
	{
		mass = 15103;
		thrust = 45000;
		acceleration = thrust / mass;
	}

	// Getters
	double getVertPosition();
	double getHorPosition();
	double getVertVelocity();
	double getHorVelocity();
	double getAngle();
	double getMass();
	double getThrust();
	double getSpeed();
	double getAcceleration();

	// Setters
	void setVertPosition(double postion);
	void setHorPosition(double position);
	void setVertVelocity(double velocity);
	void setHorVelocity(double velocity);
	void setAngle(double angle);
	void setSpeed(double speed);

private:
	double mass;
	double thrust;
	double speed;
	double position[2];
	double velocity[2];
	double angle;
	double acceleration;

};

#endif