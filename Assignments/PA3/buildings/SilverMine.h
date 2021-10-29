#ifndef SILVERMINE_H
#define SILVERMINE_H

#include "Revenue.h"
class SilverMine : public Revenue
{
public:
    SilverMine(City &city);
    ~SilverMine() = default;

    Building::Type get_type() const;
    int get_cost() const;

    std::string get_long_information() const;
    std::string get_short_information() const;

    int get_revenue() const;
};
#endif // SILVERMINE_H
