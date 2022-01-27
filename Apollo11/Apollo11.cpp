/*************************************************************
 * 1. Name:
 *      Collette Stapley, Devin Picklesimer, Spencer Wadsworth
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part of this assignment was figuring out the
 *      physics. There wasn't a video this week, so it took a while
 *      to finally get it down, which Spencer played a huge part in.
 *      Once the physics and equations were settled, dividing it up
 *      into classes was fairly smooth.
 * 5. How long did it take for you to complete the assignment?
 *      About 4-5 hours
 *****************************************************************/

// Apollo11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include "physics.h"
#include "spacecraft.h"
using namespace std;



/****************************************************************************************
* Prompts the user for the starting Vertical Velocity
****************************************************************************************/
float getVerticalVelocity() 
{
    // Get vertical velocity value from user
    float vert_vel;
    cout << "What is your vertical velocity where upwards is positive (m/s)? ";
    // Got help on how to validate input in c++ here: https://www.youtube.com/watch?v=YIX7UhIKEIk&t=378s&ab_channel=profgustin
    while (!(cin >> vert_vel)) {
        cout << "Must enter a number: ";
        cin.clear();
        cin.ignore(10, '\n');
    }
    return vert_vel;
}

/****************************************************************************************
* Prompts the user for the starting horizontal Velocity
****************************************************************************************/
float getHorizontalVelocity() 
{
    // Get horizontal velocity value from user
    float horz_vel;
    cout << "What is your horizontal velocity (m/s)? ";
    while (!(cin >> horz_vel)) {
        cout << "Must enter a number: ";
        cin.clear();
        cin.ignore(10, '\n');
    }
    return horz_vel;
}

/****************************************************************************************
* Prompts the user for the starting altitude/height/y value
****************************************************************************************/
float getAltitude() 
{
    // Get altitude value from user
    float altitude;
    cout << "What is your altitude (m)? ";
    while (!(cin >> altitude)) {
        cout << "Must enter a number: ";
        cin.clear();
        cin.ignore(10, '\n');
    }
    return altitude;
}

/****************************************************************************************
* Prompts the user for the starting angle
****************************************************************************************/
float getAngle(string prompt) 
{
    // Get altitude value from user
    float angle;
    cout << prompt;
    while (!(cin >> angle)) {
        cout << "Must enter a number: ";
        cin.clear();
        cin.ignore(10, '\n');
    }
    return angle;
}

/****************************************************************************************
* Driver runs the same loop as in main, but allows parameters to automatically fill
* inputs useful for testing
****************************************************************************************/
void driver(double vv, double hv, double vp, double ang)
{
    // sets the format for the numbers displayed
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    // Initalize physics and spacecraft objects
    Physics p;
    Spacecraft lm;

    // Get initial inputs
    /*lm.setVertVelocity(get_vertical_velocity());
    lm.setHorVelocity(get_horizontal_velocity());
    lm.setVertPosition(get_altitude());
    lm.setHorPosition(0.0);
    lm.setAngle(get_angle("What is your angle where vertical is 0 (degrees)? "));
    p.setRadians(p.computeRadians(lm.getAngle()));*/
    lm.setVertVelocity(vv);
    lm.setHorVelocity(hv);
    lm.setVertPosition(vp);
    lm.setHorPosition(0.0);
    lm.setAngle(ang);
    p.setRadians(p.computeRadians(lm.getAngle()));

    cout << endl;

    bool landed = false;
    int count = 1;

    do {

        // Simulate one second of action
        // Five times
        cout << "For the next 5 seconds with the main engine on, the position of the lander is:\n\n";

        for (int i = 0; i < 5 && lm.getVertVelocity() <= 0; i++)
        {
            lm.setVertVelocity(p.computeVelocity(
                lm.getVertVelocity(), // The lunar module's initial vertical velocity
                p.getGravity() + p.computeVectorComponent(lm.getAcceleration(), p.getRadians()),
                // The lunar module's vertical acceleration (acceleration due to gravity, plus vertical acceleration from the engines)
                1)); // One second of time elapsed

            lm.setHorVelocity(p.computeVelocity(
                lm.getHorVelocity(), // The lunar module's initial horizontal velocity
                p.computeVectorComponent(lm.getAcceleration(), (p.circleConst / 4 - p.getRadians())),
                // The lunar module's horizontal acceleration (horizontal acceleration from the engines)
                1)); // One second of time elapsed

            lm.setVertPosition(p.computePosition(
                lm.getVertPosition(), // The lunar module's initial vertical position
                lm.getVertVelocity(), // The lunar module's initial vertical velocity
                p.getGravity() + p.computeVectorComponent(lm.getAcceleration(), p.getRadians()),
                // The lunar module's vertical acceleration (acceleration due to gravity, plus vertical acceleration from the engines)
                1)); // One second of time elapsed

            lm.setHorPosition(p.computePosition(
                lm.getHorPosition(), // The lunar module's initial horizontal position
                lm.getHorVelocity(), // The lunar module's initial horizontal velocity
                p.computeVectorComponent(lm.getAcceleration(), p.circleConst / 4 - p.getRadians()),
                // The lunar module's horizontal acceleration (horizontal acceleration from the engines)
                1)); // One second of time elapsed

            lm.setSpeed(p.computeSpeed(lm.getVertVelocity(), lm.getHorVelocity()));

            cout << setw(2) << count << right << "s | (x,y): (" << lm.getHorPosition() << ", " << lm.getVertPosition() << ")  " << "(dx,dy): ("
                << lm.getHorVelocity() << ", " << lm.getVertVelocity() << ")  speed:" << lm.getSpeed() << "m/s  angle:" << lm.getAngle() << "deg" << endl;

            count++;


        }
        if (lm.getVertPosition() <= 0 || count > 9) {
            landed = true;
            if (lm.getSpeed() > 4.0) {
                cout << endl << "Rough landing!" << endl;
            }
            else {
                cout << endl << "The eagle has landed!" << endl;
            }
            break;
        }
        else {
            lm.setAngle(getAngle("\nWhat is your new angle (degrees)? "));
            p.setRadians(p.computeRadians(lm.getAngle()));

            cout << endl;
        }
    } while (!landed);
    
}

/****************************************************************************************
* Main runs the main looopand calls all necessary functions and classes
****************************************************************************************/
//int main()
//{
//    // Test Cases
//    /*cout << "Test case: Hard landing" << endl;
//    driver(-13.959, 10.53, 100.0, -45);
//    cout << endl << endl << "Test case: Crash" << endl;
//    driver(-15.000, -35.00, 207.77, 90);
//    cout << endl << endl << "Test case: Armstrong is awesome" << endl;
//    driver(-10.000, 10.000, 56.11, -42.185);*/
//    
//    // sets the format for the numbers displayed
//    cout.setf(ios::fixed);
//    cout.setf(ios::showpoint);
//    cout.precision(2);
//
//    // Initalize physics and spacecraft objects
//    Physics p;
//    Spacecraft lm;
//    
//    // Get initial inputs
//    lm.setVertVelocity(getVerticalVelocity());
//    lm.setHorVelocity(getHorizontalVelocity());
//    lm.setVertPosition(getAltitude());
//    lm.setHorPosition(0.0);
//    lm.setAngle(getAngle("What is your angle where vertical is 0 (degrees)? "));
//    p.setRadians(p.computeRadians(lm.getAngle()));
//
//    cout << endl;
//
//    bool landed = false;
//    int count = 1;
//
//    do 
//    {
//    
//    // Simulate one second of action
//    // Five times
//        cout << "For the next 5 seconds with the main engine on, the position of the lander is:\n\n";
//
//        for (int i = 0; i < 5 && lm.getVertVelocity() <= 0; i++)
//        {
//           lm.setVertVelocity(p.computeVelocity(
//                lm.getVertVelocity(), // The lunar module's initial vertical velocity
//                p.getGravity() + p.computeVectorComponent(lm.getAcceleration(), p.getRadians()),
//                // The lunar module's vertical acceleration (acceleration due to gravity, plus vertical acceleration from the engines)
//                1)); // One second of time elapsed
//
//            lm.setHorVelocity(p.computeVelocity(
//                lm.getHorVelocity(), // The lunar module's initial horizontal velocity
//                p.computeVectorComponent(lm.getAcceleration(), p.circleConst / 4 - p.getRadians()), 
//                // The lunar module's horizontal acceleration (horizontal acceleration from the engines)
//                1)); // One second of time elapsed
//
//            lm.setVertPosition(p.computePosition(
//                lm.getVertPosition(), // The lunar module's initial vertical position
//                lm.getVertVelocity(), // The lunar module's initial vertical velocity
//                p.getGravity() + p.computeVectorComponent(lm.getAcceleration(), p.getRadians()),
//                // The lunar module's vertical acceleration (acceleration due to gravity, plus vertical acceleration from the engines)
//                1)); // One second of time elapsed
//
//            lm.setHorPosition(p.computePosition(
//                lm.getHorPosition(), // The lunar module's initial horizontal position
//                lm.getHorVelocity(), // The lunar module's initial horizontal velocity
//                p.computeVectorComponent(lm.getAcceleration(), p.circleConst / 4 - p.getRadians()),
//                // The lunar module's horizontal acceleration (horizontal acceleration from the engines)
//                1)); // One second of time elapsed
//
//            lm.setSpeed(p.computeSpeed(lm.getVertVelocity(), lm.getHorVelocity()));
//            
//            cout << setw(2) << count << right << "s | (x,y): (" << lm.getHorPosition() << ", " << lm.getVertPosition() << ")  " << "(dx,dy): (" 
//                << lm.getHorVelocity() << ", " << lm.getVertVelocity() << ")  speed:" << lm.getSpeed() << "m/s  angle:" << lm.getAngle() << "deg" << endl;
//
//            count++;
//            
//            
//        }
//        if (lm.getVertPosition() <= 0 || count > 9) 
//        {
//            landed = true;
//            if (lm.getSpeed() > 4.0) {
//                cout << endl << "Rough landing!" << endl;
//            }
//            else {
//                cout << endl << "The eagle has landed!" << endl;
//            }
//            break;
//        }
//        else 
//        {
//            lm.setAngle(getAngle("\nWhat is your new angle (degrees)? "));
//            p.setRadians(p.computeRadians(lm.getAngle()));
//
//            cout << endl;
//        }
//    } while (!landed);
//
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

