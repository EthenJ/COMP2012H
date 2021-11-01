#include "Health.h" /*Health.cpp*/

Health::Health(City &city) : Building(city) {}

Building::Category Health::get_category() const
{
    return Building::Category::HEALTH;
}
