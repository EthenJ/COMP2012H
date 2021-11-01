#ifndef REVENUE_H
#define REVENUE_H

#include "Building.h"
#include "BuildingInformationFormatString.h"
// #include "..\City.h"
class Revenue : public Building
{
protected:
    explicit Revenue(City &city);

public:
    ~Revenue() = default;

    Building::Category get_category() const;
};
#endif // REVENUE_H
