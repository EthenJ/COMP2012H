#ifndef CLINIC_H
#define CLINIC_H

#include "Health.h"
class Clinic : public Health
{
public:
    Clinic(City &city);
    ~Clinic() = default;

    Building::Type get_type() const;

    int get_cost() const;

    std::string get_long_information() const;
    std::string get_short_information() const;

    int get_population_growth_rate_contribution() const override;
};
#endif // CLINIC_H
