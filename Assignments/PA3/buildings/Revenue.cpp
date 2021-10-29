#include "Revenue.h" /*Revenue.cpp*/

Revenue::Revenue(City &city) : Building(city) {}

Building::Category Revenue::get_category() const
{
    return Building::Category::REVENUE;
}

int Building::get_population() const { return 0; }

int Building::get_max_population() const { return 0; }

int Building::get_population_growth() const { return 0; }

int Building::get_population_growth_rate_contribution() const { return 0; }

void Building::increase_population(int population) {} /*do nothing*/
