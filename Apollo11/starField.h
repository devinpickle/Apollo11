#pragma once

#include "Star.h"
#include "ground.h"
#include "uiDraw.h"

const int numstars = 50;

class starField
{
	public:
		starField(Ground& grnd);
		void drawStars(ogstream& gout);
		void initializeStars();
	private:
		Ground ground;
		Star starList[numstars];
		
		
		
		


};

