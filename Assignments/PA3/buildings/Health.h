#ifndef HEALTH_H
#define HEALTH_H

#include "Building.h"
class Health : public Building
{
private:
protected:
    explicit Health(City &city, const int &population_growth_rate_contribution);
    int population_growth_rate_contribution;

public:
    ~Health();
    Building::Category get_category() const;
};
#endif // HEALTH_H
