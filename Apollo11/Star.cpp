/********************************************************************
 * Header File:
 *    star
 * Author:
 *    Devin Picklesimer, Collette Stapley, Spencer Wadsworth
 * Summary:
 *    A star class that is has a position and phase of twinkling
 *	  animation
 ********************************************************************/

#include "Star.h"


 /********************************************************************
 * Star - object with a randomnly generated starting phase
 *********************************************************************/
Star::Star(const Point& pt) :
	p(pt), // Star position
	phase(random(0,255)) // Random phase
{

}

/********************************************************************
 *
 *********************************************************************/
Star::Star()
{

}

/**********************************************************************
	 * drawStar
	 * Draws single star on screen
**********************************************************************/
void Star::drawStar(ogstream & gout)
{
	gout.drawStar(this->getPoint(), this->getPhase());
}
