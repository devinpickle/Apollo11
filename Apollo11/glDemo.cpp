/*************************************************************
 * 1. Name:
 *      Devin Picklesimer, Spencer Wadsworth, Collette Stapley
 * 2. Assignment Name:
 *      Lab 04: Apollo 11 Visuals
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      A few difficult tasks for this assignment. One was going
 *      into the given code and figuring out what the code actually
 *      does and how our code and classes can fit into what was given
 *      to us. Figuring out how to get all the stars to appear so
 *      that they don't collide with the ground was also difficult.
 *      Once you understand the given code more, however, things began
 *      to go more smoothly.
 * 5. How long did it take for you to complete the assignment?
 *      Collectively this assignment took about 4.5-5 hours. We spent
 *      a lot of this time (roughly 2 hours) going back and changing some of 
        our class designs.
 *****************************************************************/


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

    /************************************************************************
     * InitializeStars
     * Populates star array with 50 star objects, all with random positions
     * and phases
     ************************************************************************/
    void initializeStars()
    {
        for (int i = 0; i < NUMSTARS; i++)
        {
            double randomX = random(0.0, 400.0);
            double randomY = random(ground.getGroundHeight(randomX) + 10, 400.0); // Make sure stars aren't drawn on top of ground
            Point starPt(randomX, randomY);
            Star s(starPt);
            starList[i] = s; // add star to starList
        }
    }

    // this is just for test purposes.  Don't make member variables public!
    Point ptLM;           // location of the LM on the screen
    Point ptUpperRight;   // size of the screen
    double angle;         // angle the LM is pointing
    unsigned char phase;  // phase of the star's blinking
    Ground ground;
    Point ptStar;
    Star starList[NUMSTARS]; // array holds 50 stars
    Point velocity;
    Spacecraft LM; // spacecraft object
    

    
   






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
        pDemo->LM.updateFuel(true);
    }
    if (pUI->isLeft())
    {
        pDemo->LM.setHorPosition(pDemo->LM.getPosition().getX() - 1);
        pDemo->LM.updateAngle(true, false);
        pDemo->LM.updateFuel(true);
    }
    if (pUI->isUp())
    {
        pDemo->LM.setVertPosition(pDemo->LM.getPosition().getY() - 1);
        pDemo->LM.updateFuel(true);
        
    }
    if (pUI->isDown())
    {
        pDemo->LM.setVertPosition(pDemo->LM.getPosition().getY() + 1);
        pDemo->LM.updateFuel(true);
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

    // draw all our stars
    gout.drawStar(pDemo->ptStar, pDemo->phase++); // test star
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
