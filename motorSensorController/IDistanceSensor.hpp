#pragma once
#include "Enums.hpp"

class IDistanceSensor
{
public:
    virtual States GetState() = 0;
    virtual ~IDistanceSensor() = 0;
};
