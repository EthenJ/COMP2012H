#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "Building.h"
#include "BuildingInformationFormatString.h"
#include "City.h"
class Residential : public Building
{
private:
    int population;

protected:
    explicit Residential(City &city);

public:
    ~Residential() = default;

    Category get_category() const;
    int get_revenue() const;
    int get_population() const;

    virtual int get_max_population() const = 0;

    int get_population_growth_rate_contribution() const;
    int get_population_growth() const;
    void increase_population(int population);
};
#endif // RESIDENTIAL_H
