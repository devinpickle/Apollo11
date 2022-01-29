#ifndef star_h
#define star_h

#include "Point.h"





class Star
{
	public:
		Star(const Point& pt);
		Star();
		Point getPoint() { return p; }
		unsigned char getPhase() { return ++phase; }



	private:
		Point p;
		unsigned char phase;
		

};

#endif // !star_h