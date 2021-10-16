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
void Planet::determine_collision() {
	// START OF YOUR IMPLEMENTATION
	
	// END OF YOUR IMPLEMENTATION
}

/**
* Updates the acceleration of the planet. Note that this is just the sum of forces divided by the mass.
* Use the formula that is stated in the webpage.
*/
void Planet::update_acceleration() {
	// START OF YOUR IMPLEMENTATION
	
	// END OF YOUR IMPLEMENTATION
}

/**
* Updates the velocity of the planet. In one second, the main loop runs FPS times, and in each call of the main loop, STEPS 
* iterations will be called. This means there should be approximately STEPS * FPS iterations per second, and therefore the
* change in velocity should approximately be the acceleration divided by (STEPS * FPS)
*/
void Planet::update_velocity() {
	// START OF YOUR IMPLEMENTATION
	
	// END OF YOUR IMPLEMENTATION
}

/**
* Similarly, the change in displacement is approximately the velocity divided by (STEPS * FPS)
*/
void Planet::update_displacement() {
	// START OF YOUR IMPLEMENTATION
	
	// END OF YOUR IMPLEMENTATION
}