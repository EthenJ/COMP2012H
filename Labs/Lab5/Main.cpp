// Simulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

#include "Display.h"
#include "Planet.h"
#include "Simulation.h"

using namespace std;

Planet planets[MAX_PLANETS];

void play_animation() {
    //15 seconds
    for (int i = 0; i < FPS*15; ++i) {
        animation_display.clear_frame_buffer();
        for (int j = 0; j < MAX_PLANETS; ++j) {
            if (planets[j].activated) {
                animation_display.draw_circle(planets[j].x, planets[j].y, ((double)planets[j].mass) / 100, FILLED);
            }
        }

        animation_display.clear_and_draw_frame();

        this_thread::sleep_for(chrono::milliseconds(1000/FPS));
        
        for (int j = 0; j < STEPS; ++j) {
            do_single_iteration();
        }
    }
}

void play_without_animation() {
    // Same as the case of animation
    for (int i = 0; i < FPS * 15; ++i) {
        for (int j = 0; j < MAX_PLANETS; ++j) {
            if (planets[j].activated) {
                // Round to nearest integer, we don't require exact match
                int x = (int)round(planets[j].x);
                int y = (int)round(planets[j].y);
                cout << x << y;
                // Instead output the displacement of every planet
            }
        }

        //Do same thing

        for (int j = 0; j < STEPS; ++j) {
            do_single_iteration();
        }
    }
}

void configure_planets() {
    string s;
    for (int i = 0; i < MAX_PLANETS; i++) {
        cout << "Create a new planet? Type 'Y' for yes" << endl;

        cin >> s;

        if (s.at(0) != 'Y') {
            break;
        }

        cout << "Enter initial (x,y) coordinates (separated by space)" << endl;

        int x, y, vx, vy, mass;

        cin >> x;
        cin >> y;

        cout << "Enter initial (vx,vy) velocity vector (separated by space)" << endl;

        cin >> vx;
        cin >> vy;

        while (true) {
            cout << "Enter mass (1 here would be of 100 unit masses)" << endl;
            cout << "Enter a value between 1-5:  ";

            cin >> mass;

            if (mass > 0 && mass <= 5) {
                break;
            }
        }

        planets[i].x = x;
        planets[i].y = y;
        planets[i].vx = vx;
        planets[i].vy = vy;
        planets[i].mass = mass * 100;
        planets[i].activated = true;
    }

    cout << "Ready to execute simulation! Change the font size of the console to 6" << endl;
    cout << "Type 'A' to start animation. Type anything else to continue with no animation." << endl;
}

int main()
{
    for (int i = 0; i < MAX_PLANETS; ++i) {
        planets[i].uid = i;
    }
    
    configure_planets();

    char ch;
    cin >> ch;

    if(ch=='A')
        play_animation();
    else {
        play_without_animation();
    }
}