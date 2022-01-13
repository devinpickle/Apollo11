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
	}

	// Getters
	double getVertPosition();
	double getHorPosition();
	double getVertVelocity();
	double getHorVelocity();
	double getAngle();
	double getMass();

	// Setters
	void setVertPosition(double postion);
	void setHorPosition(double position);
	void setVertVelocity(double velocity);
	void setHorVelocity(double velocity);
	void setAngle(double angle);

private:
	double mass;
	double thrust;
	double position[2];
	double velocity[2];
	double angle;

};

#endif