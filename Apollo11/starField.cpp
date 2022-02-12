#include "starField.h"
#include "uiDraw.h"

// Constructor
starField::starField(Ground& grnd) : ground(grnd) 
{
    initializeStars();
}

/**********************************************************************
     * InitializeStars
     * Populates star array with 50 star objects, all with random positions
     * and phases
**********************************************************************/
void starField::initializeStars()
{
    for (int i = 0; i < numstars; i++)
    {
        double randomX = random(0.0, 400.0);
        double randomY = random(this->ground.getGroundHeight(randomX) + 10, 400.0); // Make sure stars aren't drawn on top of ground
        Point starPt(randomX, randomY);
        Star s(starPt);
        starList[i] = s; // add star to starList
    }
}

/**********************************************************************
     * drawStars
     * Draws all stars in the starfield by calling drawStar function
     * for each star
**********************************************************************/
void starField::drawStars(ogstream & gout)
{
    for (int i = 0; i < numstars; i++)
    {
        starList[i].drawStar(gout);
    }
}