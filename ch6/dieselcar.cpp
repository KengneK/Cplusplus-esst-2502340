#include "dieselcar.h"

DieselCar::DieselCar()
{

}

void DieselCar::accelerate(const float seconds)
{
    // TODO: Add formula for boosting up here!
    setSpeed(getSpeed() + mAcceleration* (seconds/3600.f));
}
