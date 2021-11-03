#include "House.h" /*House.cpp*/

House::House(City &city) : Residential(city, 0) {}
House::House(City &city, const int &population) : Residential(city, population) {}

Building::Type House::get_type() const { return Building::Type::HOUSE; }
int House::get_cost() const { return 50; }

std::string House::get_long_information() const
{
    return HOUSE_HEADER + "\n" +
           HOUSE_1_1 + std::to_string(get_population()) + "\n" +
           HOUSE_2_1 + std::to_string(get_max_population()) + "\n" +
           HOUSE_3_1 + "\n" +
           HOUSE_4_1 + std::to_string(get_population_growth_rate_contribution()) + "\n" +
           HOUSE_5_1 + "\n" +
           HOUSE_6_1 + std::to_string(get_population_growth()) +
           HOUSE_6_2 + std::to_string(get_max_population() - get_population()) + HOUSE_6_3 + "\n" + // The quota is max population - population
           HOUSE_7_1;
}

std::string House::get_short_information() const
{
    return HOUSE_HEADER + "\n" +
           HOUSE_1_1 + std::to_string(get_population()) + "\n" +
           HOUSE_2_1 + std::to_string(get_max_population()) + "\n" +
           HOUSE_4_1 + std::to_string(get_population_growth_rate_contribution()) + "\n" +
           HOUSE_6_1 + std::to_string(get_population_growth());
}

int House::get_max_population() const
{
    return 50 * (1 + number_neighboring_residential_buildings());
}