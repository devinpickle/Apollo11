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
#include "starField.h"
#include <string>  
#include <sstream> 
using namespace std;

/*************************************************************************
 * Apollo11
 * Main class that runs the "Game" simulation
 *************************************************************************/
class Apollo11
{
public:
    Apollo11(const Point& ptUpperRight) :
        ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY()),
        ground(ptUpperRight),
        LM(),
        starField(this->ground)
    {
    }


    // this is just for test purposes.  Don't make member variables public!
    Point ptLM;           // location of the LM on the screen
    Ground ground;
    Spacecraft LM; // spacecraft object
    starField starField; 
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

    // Update the spacecraft (position, velocity, fuel, etc)
    pApollo11->LM.updateSpacecraft(pUI, gout);

    // draw the ground
    pApollo11->ground.draw(gout);

    // draw spacecraft and its stats
    pApollo11->LM.drawSpacecraft(gout, pApollo11->ground);

    // draw all our stars
    pApollo11->starField.drawStars(gout);

    // Check for landing or crash collisions
    pApollo11->LM.checkCollisions(pApollo11->ground, gout);
    
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
