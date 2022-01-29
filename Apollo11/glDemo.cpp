/**********************************************************************
 * GL Demo
 * Just a simple program to demonstrate how to create an Open GL window,
 * draw something on the window, and accept simple user input
 **********************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "Star.h"
#include "spacecraft.h"
#include <string>  
#include <sstream> 
using namespace std;

const int NUMSTARS = 50;


/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(const Point& ptUpperRight) :
        ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0),
        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
        angle(0.0),
        ground(ptUpperRight),
        velocity(0.0, 0.0),
        LM(ptLM, velocity)
    {

        phase = random(0, 255);
        initializeStars();

    }

    void initializeStars()
    {
        for (int i = 0; i < NUMSTARS; i++)
        {
            double randomX = random(0.0, 400.0);
            double randomY = random(ground.getGroundHeight(randomX) + 10, 400.0);
            Point starPt(randomX, randomY);
            Star s(starPt);
            starList[i] = s;
        }
    }

    // this is just for test purposes.  Don't make member variables public!
    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    double angle;         // angle the LM is pointing
    unsigned char phase;  // phase of the star's blinking
    Ground ground;
    Point ptStar;
    Star starList[NUMSTARS];
    Point velocity;
    Spacecraft LM;
    

    
   






};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    ogstream gout;

    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    Demo* pDemo = (Demo*)p;

    // move the ship around
    if (pUI->isRight())
    {
        pDemo->LM.setHorPosition(pDemo->LM.getPosition().getX() + 1);
        pDemo->LM.updateAngle(false, true);
    }
    if (pUI->isLeft())
    {
        pDemo->LM.setHorPosition(pDemo->LM.getPosition().getX() - 1);
        pDemo->LM.updateAngle(true, false);
    }
    if (pUI->isUp())
    {
        pDemo->LM.setVertPosition(pDemo->LM.getPosition().getY() - 1);
        
    }
    if (pUI->isDown())
    {
        pDemo->LM.setVertPosition(pDemo->LM.getPosition().getY() + 1);
    }

    
    // draw the ground
    pDemo->ground.draw(gout);

    // draw the lander and its flames
    gout.drawLander(pDemo->LM.getPosition() /*position*/, pDemo->LM.getAngle() /*angle*/);
    gout.drawLanderFlames(pDemo->LM.getPosition(), pDemo->LM.getAngle(), /*angle*/
        pUI->isDown(), pUI->isLeft(), pUI->isRight());

    // put some text on the screen
    gout.setPosition(Point(5.0, 380.0));
    gout << "Fuel: " << pDemo->LM.getFuel() << "\n" <<
        "Altitude: 35 meters" << "\n" << "Speed: 12.91 m/s";

    // draw our little star
    /*for (int i = 0; i <= 50; i++)
    {
        int randomX = random()
    }*/
    gout.drawStar(pDemo->ptStar, pDemo->phase++);
    for (int i = 0; i < NUMSTARS; i++)
    {
        gout.drawStar(pDemo->starList[i].getPoint(), pDemo->starList[i].getPhase());
    }



}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Initialize OpenGL
    Point ptUpperRight(400.0, 400.0);
    Interface ui(0, NULL,
        "Open GL Demo",
        ptUpperRight);

    // Initialize the game class
    Demo demo(ptUpperRight);

    // set everything into action
    ui.run(callBack, &demo);

    return 0;
}
