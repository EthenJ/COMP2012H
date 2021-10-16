#ifndef SIMULATION_H
#define SIMULATION_H

#include "Planet.h"

const int STEPS = 100;
const int FPS = 5;

const int MAX_PLANETS = 10;

extern Planet planets[MAX_PLANETS];

void do_single_iteration();
void commit_activations();

#endif