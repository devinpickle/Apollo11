// Apollo11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "physics.h"
#include "spacecraft.h"
using namespace std;



float get_vertical_velocity() {
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

float get_horizontal_velocity() {
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

float get_altitude() {
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

float get_angle(string prompt) {
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

int main()
{
    // Initalize physics and spacecraft objects
    Physics p;
    Spacecraft lm;
    
    // Get initial inputs
    lm.setVertVelocity(get_vertical_velocity());
    lm.setHorVelocity(get_horizontal_velocity());
    lm.setVertPosition(get_altitude());
    lm.setHorPosition(0.0);
    lm.setAngle(p.computeRadians(get_angle("What is your angle where vertical is 0 (degrees)? ")));

    bool landed = false;

    do {
    
    // Simulate one second of action
    // Five times
        for (int i = 0; i < 5 && lm.getVertVelocity() <= 0; i++)
        {
            lm.setVertVelocity(p.computeVelocity(
                lm.getVertVelocity(), // The lunar module's initial vertical velocity
                p.getGravity() + p.computeVectorComponent(lm.getAcceleration(), lm.getAngle()), // The lunar module's vertical acceleration (acceleration due to gravity, plus vertical acceleration from the engines)
                1)); // One second of time elapsed

            lm.setHorVelocity(p.computeVelocity(
                lm.getHorVelocity(), // The lunar module's initial horizontal velocity
                p.computeVectorComponent(lm.getAcceleration(), p.TAU / 4 - lm.getAngle()), // The lunar module's horizontal acceleration (horizontal acceleration from the engines)
                1)); // One second of time elapsed

            lm.setVertPosition(p.computePosition(
                lm.getVertPosition(), // The lunar module's initial vertical position
                lm.getVertVelocity(), // The lunar module's initial vertical velocity
                p.getGravity() + p.computeVectorComponent(lm.getAcceleration(), lm.getAngle()), // The lunar module's vertical acceleration (acceleration due to gravity, plus vertical acceleration from the engines)
                1)); // One second of time elapsed

            lm.setHorPosition(p.computePosition(
                lm.getHorPosition(), // The lunar module's initial horizontal position
                lm.getHorVelocity(), // The lunar module's initial horizontal velocity
                p.computeVectorComponent(lm.getAcceleration(), p.TAU / 4 - lm.getAngle()), // The lunar module's horizontal acceleration (horizontal acceleration from the engines)
                1)); // One second of time elapsed


            cout << i + 1 << "s | (x,y): " << lm.getHorPosition() << ", " << lm.getVertPosition() << "   " << "(dx, dy): " << lm.getHorVelocity() << ", " << lm.getVertVelocity() << endl;

            
        }
        if (lm.getVertPosition() <= 0) {
            landed = true;
        }
        else {
            lm.setAngle(p.computeRadians(get_angle("What is your new angle (degrees)? ")));
        }
    } while (!landed);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
