/********************************************************************
 * 1. Name:
 *      Devin Picklesimer, Spencer Wadsworth, Collette Stapley
 * 2. Assignment Name:
 *      Lab 5: Apollo 11 Code Complete
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      This part was fairly easy as we already had most of it done.
 *      The hardest part was probably figuring out the logic for 
 *      switching the status of the lander, but it wasn't that bad.
 *      Simply deciding the conditions for proper landing was tough,
 *      and it's probably not the best conditions either but it 
 *      works.
 * 5. How long did it take for you to complete the assignment?
 *      Collectively this took maybe 3 hours at most?
 *      Spent a lot of time fixing formating, cleaning up, and making 
 *      sure things worked right.
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
 * Apollo11
 * Main class that runs the "Game" simulation
 *************************************************************************/
class Apollo11
{
public:
    Apollo11(const Point& ptUpperRight) :
        ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0),
        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY()),
        ground(ptUpperRight),
        velocity(0.0, 0.0),
        LM(ptLM, velocity)
    {
        phase = random(0, 255);
        initializeStars();
    }

    /**********************************************************************
     * InitializeStars
     * Populates star array with 50 star objects, all with random positions
     * and phases
     **********************************************************************/
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

/************************************************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 ************************************************************************/
void callBack(const Interface* pUI, void* p)
{
    ogstream gout;

    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    Apollo11* pApollo11 = (Apollo11*)p;

    if (pApollo11->LM.getStatus() == FlightStatus::flying) {
        if (pApollo11->LM.getFuel() > 0) {
            pApollo11->LM.updateAngle(pUI->isLeft(), pUI->isRight());
            pApollo11->LM.updateFuel(pUI->isDown(), pUI->isLeft(), pUI->isRight());
            pApollo11->LM.updateHorPosition(pUI->isDown());
            pApollo11->LM.updateVertPosition(pUI->isDown());
            pApollo11->LM.updateHorVelocity(pUI->isDown());
            pApollo11->LM.updateVertVelocity(pUI->isDown());
            // Draw lander flames if fuel is available
            gout.drawLanderFlames(pApollo11->LM.getPosition(), pApollo11->LM.getAngle(), /*angle*/
                pUI->isDown(), pUI->isLeft(), pUI->isRight());
        }
        else {
            pApollo11->LM.updateHorPosition(false);
            pApollo11->LM.updateVertPosition(false);
            pApollo11->LM.updateHorVelocity(false);
            pApollo11->LM.updateVertVelocity(false);
        }
        
    }

    // draw the ground
    pApollo11->ground.draw(gout);

    // draw the lander and its flames
    gout.drawLander(pApollo11->LM.getPosition() /*position*/, pApollo11->LM.getAngle() /*angle*/);

    // put some text on the screen
    gout.setPosition(Point(5.0, 380.0));
    gout << "Fuel: " << pApollo11->LM.getFuel() << "\n" <<
        "Altitude: " << fixed<<setprecision(0)<<pApollo11->ground.getElevation(pApollo11->LM.getPosition()) << " meters" << "\n" << 
        "Speed: " << fixed<<setprecision(2)<<pApollo11->LM.getSpeed() << " m/s";

    // draw all our stars
    gout.drawStar(pApollo11->ptStar, pApollo11->phase++); // test star
    for (int i = 0; i < NUMSTARS; i++)
    {
        gout.drawStar(pApollo11->starList[i].getPoint(), pApollo11->starList[i].getPhase());
    }

    // Collisions
    // Check for successful landing
    if (pApollo11->ground.onPlatform(pApollo11->LM.getPosition(), 20))
    {
        if (abs(pApollo11->LM.getAngle()) <= 0.3 && pApollo11->LM.getSpeed() <= 8.0)
            pApollo11->LM.updateStatus(FlightStatus::landed);  
        else 
            pApollo11->LM.updateStatus(FlightStatus::crashed);   
    }
    else if (pApollo11->ground.hitGround(pApollo11->LM.getPosition(), 20))
        pApollo11->LM.updateStatus(FlightStatus::crashed);

    switch (pApollo11->LM.getStatus())
    {
        case FlightStatus::landed:
            pApollo11->LM.setAngle(0.0);
            gout.setPosition(Point(250.0, 380.0));
            gout << "The Eagle has landed!";
            break;
        case FlightStatus::crashed:
            pApollo11->LM.setAngle(3.14);
            gout.setPosition(Point(250.0, 380.0));
            gout << "Houston We Have A Problem";
            break;
    }
}

/************************************************************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 ************************************************************************/
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
        "Open Apollo 11 Simulator",
        ptUpperRight);

    // Initialize the game class
    Apollo11 game(ptUpperRight);

    // set everything into action
    ui.run(callBack, &game);

    return 0;
}
