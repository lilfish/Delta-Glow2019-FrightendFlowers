#pragma once
#include "Enums.hpp"

class IDistanceSensor
{
public:
    virtual States GetState() = 0;
    virtual int UpdateRestlessness(int distance) = 0;
    virtual ~IDistanceSensor() {}
};
