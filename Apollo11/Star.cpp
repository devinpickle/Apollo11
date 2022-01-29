#include "Star.h"
#include "uiDraw.h"

Star::Star(const Point& pt) :
	p(pt), // Star position
	phase(random(0,255)) // Random phase
{

}

Star::Star()
{

}
