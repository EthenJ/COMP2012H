#include "Revenue.h" /*Revenue.cpp*/

Revenue::Revenue(City &city) : Building(city) {}

Building::Category Revenue::get_category() const
{
    return Building::Category::REVENUE;
}
