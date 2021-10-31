#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "Revenue.h"
class GoldMine : public Revenue
{
public:
    GoldMine(City &city);
    ~GoldMine() = default;

    Building::Type get_type() const;
    int get_cost() const;

    std::string get_long_information() const;
    std::string get_short_information() const;

    int get_revenue() const;
};
#endif // GOLDMINE_H
