/********************************************************************
 * Header File:
 *    star
 * Author:
 *    Devin Picklesimer, Collette Stapley, Spencer Wadsworth
 * Summary:
 *    A star class that is has a position and phase of twinkling 
 *	  animation
 ********************************************************************/

#ifndef star_h
#define star_h

#include "Point.h"
#include "uiDraw.h"

class Star
{
	public:
		// Constructors
		Star(const Point& pt);
		Star();

		// Getters
		Point getPoint() { return p; }
		unsigned char getPhase() { return ++phase; }

		void drawStar(ogstream & gout);

		

	private:
		Point p;
		unsigned char phase;
};

#endif // !star_h