#include "Health.h" /*Health.cpp*/

Health::Health(City &city) : Building(city) {}

Building::Category Health::get_category() const
{
    return Building::Category::HEALTH;
}

int Health::get_population() const { return 0; }

int Health::get_max_population() const { return 0; }

int Health::get_revenue() const { return 0; }

int Health::get_population_growth() const { return 0; }

void Health::increase_population(int population) {} /*do nothing*/

/*virtual funcitons*/
int Health::get_population_growth_rate_contribution() const {}