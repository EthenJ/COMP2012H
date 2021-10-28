#ifndef HEALTH_H
#define HEALTH_H

#include "Building.h"
#include "BuildingInformationFormatString.h"
class Health : public Building
{
private:
protected:
    explicit Health(City &city);

public:
    ~Health();

    Building::Category get_category() const;

    int get_population() const;
    int get_max_population() const;
    int get_revenue() const;
    int get_population_growth() const;

    void increase_population(int population);
};
#endif // HEALTH_H
