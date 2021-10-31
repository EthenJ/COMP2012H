#ifndef HEALTH_H
#define HEALTH_H

#include "Building.h"
#include "BuildingInformationFormatString.h"
class Health : public Building
{
protected:
    explicit Health(City &city);

public:
    ~Health() = default;

    Building::Category get_category() const;

    int get_population() const;
    int get_max_population() const;
    int get_revenue() const;
    int get_population_growth() const;

    void increase_population(int population);

    virtual Building::Type get_type() const = 0;
    virtual int get_cost() const = 0;
    virtual std::string get_long_information() const = 0;
    virtual std::string get_short_information() const = 0;
    virtual int get_population_growth_rate_contribution() const;
};
#endif // HEALTH_H
