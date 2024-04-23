#ifndef ELECTRICCAR_H
#define ELECTRICCAR_H

#include "pkw.h"

class ElectricCar : public PKW
{
public:
    ElectricCar();

    void accelerate(const float seconds) override;

private:

    const float mAcceleration = 20000.0f; // km/(h^2)
};

#endif // ELECTRICCAR_H
