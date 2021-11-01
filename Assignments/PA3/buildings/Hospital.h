#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Health.h"
class Hospital : public Health
{
public:
    Hospital(City &city);
    ~Hospital() = default;

    Building::Type get_type() const;

    int get_cost() const;

    std::string get_long_information() const;
    std::string get_short_information() const;

    int get_population_growth_rate_contribution() const override;
};
#endif // HOSPITAL_H
