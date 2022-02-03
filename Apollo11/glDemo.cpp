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
#include <iomanip>
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
        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY()),
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

    //// move the ship around
    //if (pUI->isRight())
    //{
    //    pDemo->LM.setHorPosition(pDemo->LM.getPosition().getX() + 1);
    //    
    //}
    //if (pUI->isLeft())
    //{
    //    pDemo->LM.setHorPosition(pDemo->LM.getPosition().getX() - 1);
    //    
    //}
    //if (pUI->isUp())
    //{
    //    pDemo->LM.setVertPosition(pDemo->LM.getPosition().getY() - 1);
    //    
    //}
    //if (pUI->isDown())
    //{
    //    pDemo->LM.setVertPosition(pDemo->LM.getPosition().getY() + 1);
    //}

    

    if (pDemo->LM.getStatus() == FlightStatus::flying) {
        if (pDemo->LM.getFuel() > 0) {
            pDemo->LM.updateAngle(pUI->isLeft(), pUI->isRight());
            pDemo->LM.updateFuel(pUI->isDown(), pUI->isLeft(), pUI->isRight());
            pDemo->LM.updateHorPosition(pUI->isDown());
            pDemo->LM.updateVertPosition(pUI->isDown());
            pDemo->LM.updateHorVelocity(pUI->isDown());
            pDemo->LM.updateVertVelocity(pUI->isDown());
            // Draw lander flames if fuel is available
            gout.drawLanderFlames(pDemo->LM.getPosition(), pDemo->LM.getAngle(), /*angle*/
                pUI->isDown(), pUI->isLeft(), pUI->isRight());
        }
        else {
            pDemo->LM.updateHorPosition(false);
            pDemo->LM.updateVertPosition(false);
            pDemo->LM.updateHorVelocity(false);
            pDemo->LM.updateVertVelocity(false);
        }
        
    }
    


    // draw the ground
    pDemo->ground.draw(gout);

    // draw the lander and its flames
    gout.drawLander(pDemo->LM.getPosition() /*position*/, pDemo->LM.getAngle() /*angle*/);
    

    // put some text on the screen
    gout.setPosition(Point(5.0, 380.0));
    gout << "Fuel: " << pDemo->LM.getFuel() << "\n" <<
        "Altitude: " << fixed<<setprecision(0)<<pDemo->ground.getElevation(pDemo->LM.getPosition()) << " meters" << "\n" << 
        "Speed: " << fixed<<setprecision(2)<<pDemo->LM.getSpeed() << " m/s";

    // draw all our stars
    gout.drawStar(pDemo->ptStar, pDemo->phase++); // test star
    for (int i = 0; i < NUMSTARS; i++)
    {
        gout.drawStar(pDemo->starList[i].getPoint(), pDemo->starList[i].getPhase());
    }

    // Collisions
    // Check for successful landing
    if (pDemo->ground.onPlatform(pDemo->LM.getPosition(), 20))
    {
        if (abs(pDemo->LM.getAngle()) <= 0.3 && pDemo->LM.getSpeed() <= 8.0)
            pDemo->LM.updateStatus(FlightStatus::landed);  
        else 
            pDemo->LM.updateStatus(FlightStatus::crashed);   
    }
    else if (pDemo->ground.hitGround(pDemo->LM.getPosition(), 20))
        pDemo->LM.updateStatus(FlightStatus::crashed);

    switch (pDemo->LM.getStatus())
    {
        case FlightStatus::landed:
            pDemo->LM.setAngle(0.0);
            gout.setPosition(Point(250.0, 380.0));
            gout << "The Eagle has landed!";
            break;
        case FlightStatus::crashed:
            pDemo->LM.setAngle(3.14);
            gout.setPosition(Point(250.0, 380.0));
            gout << "Houston We Have A Problem";
            break;
    }
    
    //{
    //    pDemo->LM.updateStatus(FlightStatus::landed);
    //    pDemo->LM.setAngle(0.0);
    //    gout.setPosition(Point(250.0, 380.0));
    //    gout << "The Eagle has landed!";
    //}
    //// Check for ground crash
    //else if (pDemo->ground.hitGround(pDemo->LM.getPosition(), 20))
    //{
    //    pDemo->LM.updateStatus(FlightStatus::crashed);
    //    pDemo->LM.setAngle(3.14);
    //    gout.setPosition(Point(250.0, 380.0));
    //    gout << "Houston We Have A Problem";
    //    
    //    
    //}


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
