#ifndef DIESELCAR_H
#define DIESELCAR_H

#include "pkw.h"

class DieselCar : public PKW
{
public:

    DieselCar();
    
    // TODO: Override accelerate
    virtual void accelerate(const float seconds) override;

private:

    const float mAcceleration = 10000.0f; // km/(h^2)
};

#endif // DIESELCAR_H
