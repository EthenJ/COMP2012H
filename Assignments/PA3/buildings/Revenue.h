#ifndef REVENUE_H
#define REVENUE_H

#include "Building.h"
#include "BuildingInformationFormatString.h"
#include "City.h"
class Revenue : public Building
{
private:
protected:
    explicit Revenue(City &city);

public:
    ~Revenue() = default;

    Building::Category get_category() const;
    int get_population() const;
    int get_max_population() const;
    int get_population_growth() const;
    int get_population_growth_rate_contribution() const;
    void increase_population(int population);
    /*
        virtual Building::Type get_type() const = 0;

        virtual int get_cost() const = 0;

        virtual std::string get_long_information() const = 0;

        virtual std::string get_short_information() const = 0;

        virtual int get_revenue() const;*/

};
#endif // REVENUE_H
