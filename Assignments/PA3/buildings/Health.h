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
};
#endif // HEALTH_H
