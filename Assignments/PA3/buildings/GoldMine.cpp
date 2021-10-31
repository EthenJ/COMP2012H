#include "..\City.h" /*GoldMine.cpp*/

GoldMine::GoldMine(City &city) : Revenue(city) {}

Building::Type GoldMine::get_type() const { return Building::Type::GOLD_MINE; }
int GoldMine::get_cost() const { return 400; }

std::string GoldMine::get_long_information() const
{
    return GOLD_HEADER + "\n" +
           GOLD_1_1 + std::to_string(get_revenue()) + "\n" +
           GOLD_2_1;
}

std::string GoldMine::get_short_information() const
{
    return GOLD_HEADER + "\n" +
           GOLD_1_1 + std::to_string(get_revenue()) + "\n";
}

int GoldMine::get_revenue() const
{
    // For Gold Mines, it is city's population + population in neighboring buildings.
    return 2 * (city.get_population() + number_neighboring_population());
}