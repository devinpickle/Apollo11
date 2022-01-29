#pragma once

#include "Point.h"

#ifndef star_h
#define star_h



class Star
{
	public:
		Point getPoint() { return p; }
		unsigned char getPhase() { return phase; }



	private:
		Point p = Point(200, 300);
		unsigned char phase = rand() % 255;
		

};

#endif // !star_h