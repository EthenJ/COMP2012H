#ifndef HOUSE_H
#define HOUSE_H

#include "Residential.h"
class House : public Residential
{
protected:
    explicit House(City &city);

public:
    explicit House(City &city);
    ~House() = default;

    Building::Type get_type() const;
    int get_cost() const;

    std::string get_long_information() const;
    std::string get_short_information() const;

    int get_max_population() const;
};
#endif // HOUSE_H
