#include <cmath>
#include "Planet.h"
#include "Simulation.h"

using namespace std;

/**
* Deactivates planets when a collision occurs, based on the following rule (say we have planets A,B):
* If the distance between A, B is less than 0.1,
*	Deactivate the planet with the smaller mass
*   If the masses are equal, deactivate both
* Note that as the loops themselves use the attribute 'activated', do not deactivate the planets
* by setting 'activated' to false directly. Set flag_deactivate to true, and it will be deactivated
* later in your do_single_iteration function. 
*/
void Planet::determine_collision()
{
	// START OF YOUR IMPLEMENTATION
	if (activated)
	{
		for (int j = uid + 1; j < MAX_PLANETS; j++)
		{
			if (planets[j].activated)
			{
				if (std::hypot((x - planets[j].x), (y - planets[j].y)) < 0.1)
				{
					if (mass == planets[j].mass)
					{
						flag_deactivate = true;
						planets[j].flag_deactivate = true;
					}
					else if (mass > planets[j].mass)
					{
						planets[j].flag_deactivate = true;
					}
					else if (mass < planets[j].mass)
					{
						flag_deactivate = true;
					}
				}
			}
		}
	}
	// END OF YOUR IMPLEMENTATION
}

/**
* Updates the acceleration of the planet. Note that this is just the sum of forces divided by the mass.
* Use the formula that is stated in the webpage.
*/
void Planet::update_acceleration()
{
	// START OF YOUR IMPLEMENTATION
	if (activated)
	{
		ax = 0;
		ay = 0;
		for (int j = 0; j < MAX_PLANETS; j++)
		{
			if (planets[j].activated && j != uid)
			{
				double dx = planets[j].x - x;
				double dy = planets[j].y - y;
				double r = std::hypot(dx, dy);
				ax += planets[j].mass * dx / (r * r * r);
				ay += planets[j].mass * dy / (r * r * r);
			}
		}
	}

	// END OF YOUR IMPLEMENTATION
}
/**
* Updates the velocity of the planet. In one second, the main loop runs FPS times, and in each call of the main loop, STEPS 
* iterations will be called. This means there should be approximately STEPS * FPS iterations per second, and therefore the
* change in velocity should approximately be the acceleration divided by (STEPS * FPS)
*/
void Planet::update_velocity()
{
	// START OF YOUR IMPLEMENTATION
	if (activated)
	{
		vx += ax / (STEPS * FPS);
		vy += ay / (STEPS * FPS);
	}
	// END OF YOUR IMPLEMENTATION
}

/**
* Similarly, the change in displacement is approximately the velocity divided by (STEPS * FPS)
*/
void Planet::update_displacement()
{
	// START OF YOUR IMPLEMENTATION
	if (activated)
	{
		x += vx / (STEPS * FPS);
		y += vy / (STEPS * FPS);
	}
	// END OF YOUR IMPLEMENTATION
}