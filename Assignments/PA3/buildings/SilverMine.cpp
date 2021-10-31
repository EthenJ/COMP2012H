#include "..\\City.h" /*SilverMine.cpp*/

SilverMine::SilverMine(City &city) : Revenue(city) {}

Building::Type SilverMine::get_type() const { return Building::Type::SILVER_MINE; }
int SilverMine::get_cost() const { return 50; }

std::string SilverMine::get_long_information() const
{
    return SILVER_HEADER + "\n" +
           SILVER_1_1 + std::to_string(get_revenue()) + "\n" +
           SILVER_2_1;
}

std::string SilverMine::get_short_information() const
{
    return SILVER_HEADER + "\n" +
           SILVER_1_1 + std::to_string(get_revenue()) + "\n";
}

int SilverMine::get_revenue() const
{
    // For Silver Mines, it is city's population + population in neighboring buildings.
    return city.get_population() + number_neighboring_population();
}