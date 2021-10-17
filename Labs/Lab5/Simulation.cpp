#include "Simulation.h"

/**
* Deactivates all the planets, which are flagged to be deactivated
*/
void commit_activations()
{
	for (int i = 0; i < MAX_PLANETS; ++i)
	{
		planets[i].activated = planets[i].activated & !planets[i].flag_deactivate;
	}
}

/**
* Runs a single iteration of the simulation of the planets.
* Only call the respective functions on activated planets
*/
void do_single_iteration()
{
	// START OF YOUR IMPLEMENTATION

	// First check the collisions of the planets
	for (int i = 0; i < MAX_PLANETS; i++)
	{
		planets[i].determine_collision();
	}

	// Deactivate all the planets that are flagged to be removed from the previous methods
	commit_activations();

	// Update the acceleration
	for (int i = 0; i < MAX_PLANETS; i++)
	{
		planets[i].update_acceleration();
	}

	// Update the velocity
	for (int i = 0; i < MAX_PLANETS; i++)
	{
		planets[i].update_velocity();
	}

	// Update the displacement
	for (int i = 0; i < MAX_PLANETS; i++)
	{
		planets[i].update_displacement();
	}

	// END OF YOUR IMPLEMENTATION
}