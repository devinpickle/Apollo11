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

#include "Point.h"
#include "physics.h"

enum class FlightStatus { flying, landed, crashed }; // Outside the class so anyone can use it without referencing class

class Spacecraft
{

private:
	Point position;
	Point velocity;
	double angle;
	double acceleration;
	double fuel;
	FlightStatus status;
	Physics p;
	

public:
	// Constructor
	Spacecraft();

	Spacecraft(const Point& pos, const Point& vel);

	// Getters
	Point getPosition();
	Point getVelocity();
	double getAngle();
	double getAcceleration();
	double getFuel();

	// Setters
	void setVertPosition(double postion);
	void setHorPosition(double position);
	void setVertVelocity(double velocity);
	void setHorVelocity(double velocity);
	void setAngle(double angle);
	
	void updateVertPosition(bool mainThrust);
	void updateHorPosition(bool mainThrust);
	void updateAngle(bool leftThrust, bool rightThrust);
	void updateVertVelocity(bool mainThrust);
	void updateHorVelocity(bool mainThrust);
	void updateFuel(bool mainThrust);
	void updateStatus(FlightStatus stat);

	




};

#endif