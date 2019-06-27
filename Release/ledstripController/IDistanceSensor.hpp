#pragma once
#include "Enums.hpp"

class IDistanceSensor
{
public:
    virtual int GetDistance() = 0;
    virtual int PotentioSetDistance() = 0;
    virtual int CalculateRestlesness(States state) = 0;
    virtual States CalculateRestlesness(int restlesness) = 0;
    virtual ~IDistanceSensor() {}
};
