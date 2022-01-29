#include "Star.h"
#include "uiDraw.h"

Star::Star(const Point& pt) :
	p(pt), 
	phase(random(0,255))
{

}

Star::Star()
{

}
