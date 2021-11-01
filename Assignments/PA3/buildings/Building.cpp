#include "Building.h" /*Building.cpp*/

/* set reference of city*/
Building::Building(City &city) : city(city) {}

/*Common functions for all types of building.
 *[Registers/Deregisters] the building referred by the pointer (never a nullptr) to the neighboring_buildings array.
 *If the building is already [registered/already unregistered, or not registered], return false.
 *Otherwise, return true. The order of buildings in the array does not matter.*/
bool Building::register_neighboring_building(Building *building)
{
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] == building) // If the building is already [registered]
        {
            return false;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] == nullptr)
        {
            neighboring_buildings[i] = building; // [Registers] the building
            return true;
        }
    }

    return false; // no place to register, not registered
}

/*Common functions for all types of building.
 *[Registers/Deregisters] the building referred by the pointer (never a nullptr) to the neighboring_buildings array.
 *If the building is already [registered/already unregistered, or not registered], return false.
 *Otherwise, return true. The order of buildings in the array does not matter.*/
bool Building::deregister_neighboring_building(Building *building)
{
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] == building) // If the building is [registered]
        {
            neighboring_buildings[i] = nullptr; // [Deregisters] the building
            return true;
        }
    }
    return false; // [already unregistered]
}

/*Returns the number of neighboring buildings that are Residential buildings.*/
int Building::number_neighboring_residential_buildings() const
{
    int neighboring_residential_buildings = 0;
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] != nullptr &&
            ((neighboring_buildings[i]->get_category()) == Building::Category::RESIDENTIAL))
        {
            neighboring_residential_buildings++;
        }
    }
    return neighboring_residential_buildings;
}

/*Returns the number of neighboring buildings that are Health buildings.*/
int Building::number_neighboring_health_buildings() const
{
    int neighboring_health_buildings = 0;
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] != nullptr &&
            ((neighboring_buildings[i]->get_category()) == Building::Category::HEALTH))
        {
            neighboring_health_buildings++;
        }
    }
    return neighboring_health_buildings;
}

/*Returns the number of neighboring buildings that are Gold Mines.*/
int Building::number_neighboring_gold_mines() const
{
    int neighboring_gold_mines = 0;
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] != nullptr &&
            ((neighboring_buildings[i]->get_type()) == Building::Type::GOLD_MINE))
        {
            neighboring_gold_mines++;
        }
    }
    return neighboring_gold_mines;
}

/*Returns the sum of population in neighboring buildings.*/
int Building::number_neighboring_population() const
{
    int neighboring_population = 0;
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] != nullptr)
        {
            neighboring_population += neighboring_buildings[i]->get_population();
        }
    }
    return neighboring_population;
}

int Building::get_revenue() const { return 0; }
int Building::get_population() const { return 0; }
int Building::get_max_population() const { return 0; }
int Building::get_population_growth() const { return 0; }
int Building::get_population_growth_rate_contribution() const { return 0; }
void Building::increase_population(int population) { return; }