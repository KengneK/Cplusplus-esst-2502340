#include "fahrzeug.h"

#include <iostream>

Fahrzeug::Fahrzeug()
{

}

void Fahrzeug::showValues() const
{
    // TODO: Show speed only
    std::cout << "Speed is : " << getSpeed() << "m/s. ";
}

float Fahrzeug::getSpeed() const
{
    return mSpeed;
}

void Fahrzeug::setSpeed(float newSpeed)
{
    mSpeed = newSpeed;
}
