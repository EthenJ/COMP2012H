#include "..\City.h" /*Clinic.cpp*/

Clinic::Clinic(City &city) : Health(city) {}

Building::Type Clinic::get_type() const
{
    return Building::Type::CLINIC;
}

int Clinic::get_cost() const
{
    return 50;
}

std::string Clinic::get_long_information() const
{
    return CLINIC_HEADER + "\n" +
           CLINIC_1_1 + std::to_string(get_population_growth_rate_contribution()) + "\n" +
           CLINIC_2_1;
}

std::string Clinic::get_short_information() const
{
    return CLINIC_HEADER + "\n" +
           CLINIC_1_1 + std::to_string(get_population_growth_rate_contribution());
}

int Clinic::get_population_growth_rate_contribution() const
{
    return 60 / (1 + number_neighboring_health_buildings());
}