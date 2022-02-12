/***********************************************************************
 * Header File:
 *    Starfield : Represents the stars in the sky in the lunar lander game
 * Author:
 *    Devin Picklesimer
 * Summary:
 *    Creates all stars in game and draws them
 ************************************************************************/
#pragma once

#include "Star.h"
#include "ground.h"
#include "uiDraw.h"

const int numstars = 50;

class starField
{
	public:
		starField(Ground& grnd); // Constructor
		void drawStars(ogstream& gout);
		void initializeStars(); // Create list of stars
	private:
		Ground ground;
		Star starList[numstars]; // List of star objects
		
		
		
		


};

