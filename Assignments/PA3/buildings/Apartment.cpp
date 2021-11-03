#include "Apartment.h" /*Apartment.cpp*/

Apartment::Apartment(City &city) : Residential(city, 0) {}
Apartment::Apartment(City &city, const int &population) : Residential(city, population) {}

Building::Type Apartment::get_type() const { return Building::Type::APARTMENT; }
int Apartment::get_cost() const { return 300; }

std::string Apartment::get_long_information() const
{
    return APARTMENT_HEADER + "\n" +
           APARTMENT_1_1 + std::to_string(get_population()) + "\n" +
           APARTMENT_2_1 + std::to_string(get_max_population()) + "\n" +
           APARTMENT_3_1 + "\n" +
           APARTMENT_4_1 + std::to_string(get_population_growth_rate_contribution()) + "\n" +
           APARTMENT_5_1 + "\n" +
           APARTMENT_6_1 + std::to_string(get_population_growth()) +
           APARTMENT_6_2 + std::to_string(get_max_population() - get_population()) + APARTMENT_6_3 + "\n" + // The quota is max population - population
           APARTMENT_7_1;
}

std::string Apartment::get_short_information() const
{
    return APARTMENT_HEADER + "\n" +
           APARTMENT_1_1 + std::to_string(get_population()) + "\n" +
           APARTMENT_2_1 + std::to_string(get_max_population()) + "\n" +
           APARTMENT_4_1 + std::to_string(get_population_growth_rate_contribution()) + "\n" +
           APARTMENT_6_1 + std::to_string(get_population_growth());
}

int Apartment::get_max_population() const
{
    return 250 * (1 + number_neighboring_residential_buildings());
}
