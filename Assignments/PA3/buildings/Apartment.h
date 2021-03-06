#ifndef APARTMENT_H
#define APARTMENT_H

#include "Residential.h"
class Apartment : public Residential
{
public:
    explicit Apartment(City &city);
    explicit Apartment(City &city, const int &population);
    ~Apartment() = default;

    Building::Type get_type() const;
    int get_cost() const;

    std::string get_long_information() const;
    std::string get_short_information() const;

    int get_max_population() const override;
};
#endif // APARTMENT_H
