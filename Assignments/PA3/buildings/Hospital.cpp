#include "Hospital.h" /*Hospital.cpp*/

Hospital::Hospital(City &city) : Health(city) {}

Building::Type Hospital::get_type() const
{
    return Building::Type::HOSPITAL;
}

int Hospital::get_cost() const
{
    return 500;
}

std::string Hospital::get_long_information() const
{
    return HOSPITAL_HEADER + "\n" +
           HOSPITAL_1_1 + std::to_string(get_population_growth_rate_contribution()) + "\n" +
           HOSPITAL_2_1;
}

std::string Hospital::get_short_information() const
{
    return HOSPITAL_HEADER + "\n" +
           HOSPITAL_1_1 + std::to_string(get_population_growth_rate_contribution());
}

int Hospital::get_population_growth_rate_contribution() const
{
    return 360 / (1 + number_neighboring_health_buildings());
}