#include "..\\City.h" /*Residential.cpp*/

Residential::Residential(City &city) : Building(city), population(0) {}

Building::Category Residential::get_category() const
{
    return Building::Category::RESIDENTIAL;
}

int Residential::get_revenue() const { return 0; }

int Residential::get_population() const { return population; }

int Residential::get_population_growth() const
{
    int population_growth = city.get_population_growth_rate() *
                            (number_neighboring_health_buildings() - number_neighboring_gold_mines()) / 10;
    int limit = get_max_population() - population;

    if (population_growth < limit)
    {
        return population_growth;
    }
    return limit;
}

int Residential::get_population_growth_rate_contribution() const { return -get_population(); }

void Residential::increase_population(int population)
{
    this->population += population;
    /*If the new population exceeds the max population, set it to the max population.*/
    if (population > get_max_population())
    {
        this->population = get_max_population();
    }

    /*If the new population is smaller than 0, set it to 0.*/
    else if (this->population < 0)
    {
        this->population = 0;
    }
}