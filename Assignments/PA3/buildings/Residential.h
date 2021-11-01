#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "Building.h"
#include "BuildingInformationFormatString.h"
// #include "..\City.h"
class Residential : public Building
{
private:
    int population;

protected:
    explicit Residential(City &city);

public:
    ~Residential() = default;

    Category get_category() const;

    int get_population() const override;

    int get_population_growth_rate_contribution() const override;
    int get_population_growth() const override;
    void increase_population(int population) override;
};
#endif // RESIDENTIAL_H
