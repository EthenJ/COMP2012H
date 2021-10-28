#include "Health.h"

Health::Health(City &city, const int &population_growth_rate_contribution) : Building(city)
{
    this->population_growth_rate_contribution = population_growth_rate_contribution;
}

Building::Category get_category()
{
    return Building::Category::HEALTH;
}
/*
    virtual Building::Type get_type() const = 0;

    virtual int get_cost() const = 0;

    virtual std::string get_long_information() const = 0;

    virtual std::string get_short_information() const = 0;

    virtual int get_revenue() const;
    virtual int get_population() const;
    virtual int get_max_population() const;
    virtual int get_population_growth() const;
    virtual int get_population_growth_rate_contribution() const;
    virtual void increase_population(int population);*/